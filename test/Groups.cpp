#include <iostream>
#include "RoukaVici.hh"

int main()
{
    int testNbr = 1;
    RoukaVici *rv = new RoukaVici();
    if (rv->NewGroup("TestGroup")) goto error;
    testNbr++;
    if (rv->NewGroup("TestGroup") != 1) goto error;
    testNbr++;
    if (rv->AddToGroup("TestGroup", 0) || rv->AddToGroup("TestGroup", 1)) goto error;
    testNbr++;
    if (rv->VibrateGroup("TestGroup", 255)) goto error;
    testNbr++;
    if (rv->VibrateGroup("ImaginaryGroup", 255) != 3) goto error; // Check that nonexistent groups trigger an error
    testNbr++;
    if (rv->RmFromGroup("ImaginaryGroup", 0) != 2) goto error; // Check that nonexistent groups trigger an error
    testNbr++;
    if (rv->RmFromGroup("TestGroup", 42) != 1) goto error; // Check that nonexistent motor triggers an error
    testNbr++;
    if (rv->AddToGroup("TestGroup", 0) != 1) goto error; // Check that already-existing motor triggers an error
    testNbr++;
    delete rv;
    return 0;
error:
    // std::cerr << "Test #" << testNbr << " failed" << std::endl;
    delete rv;
    return 1;
}