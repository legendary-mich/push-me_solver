#ifndef VMBOARDSOLVE_H
#define VMBOARDSOLVE_H

#include "vmboardbase.h"
#include "Solver/solver.h"

class VMBoardSolve : public VMBoardBase
{
    Q_OBJECT
    Q_PROPERTY(bool solveEnabled READ solveEnabled NOTIFY solveEnabledChanged)
    Q_PROPERTY(bool undoEnabled READ undoEnabled NOTIFY undoEnabledChanged)
    Q_PROPERTY(bool forwardEnabled READ forwardEnabled NOTIFY forwardEnabledChanged)
    Q_PROPERTY(int depth READ depth WRITE setDepth NOTIFY depthChanged)
    //Q_PROPERTY(QString message READ message NOTIFY messageChanged)
public:
    explicit VMBoardSolve(QObject *parent = 0);
    bool solveEnabled(){return _moves.size()==0;}
    bool undoEnabled()const{return _moves.size() > 0 && _currentMove > 0;}
    bool forwardEnabled()const{return (int)_moves.size() > 0 && _currentMove<(int)_moves.size();}
    int depth()const{return _depth;}
    void setDepth(int depth){_depth = depth; emit depthChanged();}
    //QString message()const{return _message;}
    void SetBoardClone(const PushMe::BoardBase *board)override;
signals:
    void solveEnabledChanged();
    void undoEnabledChanged();
    void forwardEnabledChanged();
    void depthChanged();
    void messageChanged();
public slots:
    void loadBoard(QString fullPath) override;
    void mousePressed(float mouseX, float mouseY, bool shiftPressed) override{Q_UNUSED(mouseX);Q_UNUSED(mouseY);Q_UNUSED(shiftPressed);}
    void mouseMoved(float mouseX, float mouseY) override{Q_UNUSED(mouseX); Q_UNUSED(mouseY);}
    void mouseReleased() override{}
    void solve();
    void undo();
    void forward();
private:
    bool _canSolve{false};
    int _depth;
    int _currentMove;
    std::unique_ptr<PushMe::Solver> _solver;
    std::vector<PushMe::MoveDescription> _moves;
    void EmitAllButtons(){emit solveEnabledChanged(); emit undoEnabledChanged(); emit forwardEnabledChanged(); emit messageChanged();}
};

#endif // VMBOARDSOLVE_H
