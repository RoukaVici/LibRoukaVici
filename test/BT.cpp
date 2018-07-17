#include "RoukaVici.hh"

int main()
{
    RoukaVici *rv = new RoukaVici();
    if (rv->ChangeDeviceManager("BTManager")) goto error;
    if (rv->FindDevice()) goto error;
    if (rv->Vibrate(0, 0) || rv->Vibrate(1, 1)) goto error;
    delete rv;
    return 0;
error:
    delete rv;
    return 1;
}