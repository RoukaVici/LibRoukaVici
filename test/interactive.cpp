#include <iostream>
#include "RoukaVici.hh"

void PrintHelp()
{
  std::cerr << "Commands:" << std::endl;
  std::cerr << "v: Send a vibration" << std::endl;
  std::cerr << "c: Change Device Manager" << std::endl;
  std::cerr << "l: Change Log Method" << std::endl;
  std::cerr << "h: Print this help message" << std::endl;
  std::cerr << "q: Quit this program" << std::endl;
}

void  GetInput(std::string& input)
{
  std::cerr << "<RV> ";
  std::getline(std::cin, input);
  while (input[0] == 0)
  {
    std::getline(std::cin, input);
  }
}

int main() {
  RoukaVici *rv = new RoukaVici();  // Initialize the library

  std::cerr << "Welcome to the RoukaVici interactive command line" << std::endl;
  std::cerr << "This program will let you interact with your glove using a very barebones command list" << std::endl << std::endl;
  PrintHelp();

  std::string input;
  GetInput(input);
  while (input != "q")
    {
      if (input.length() > 0)
        {
          if (input[0] == 'v')
            {
              std::cerr << "Enter motor number M and intensity I (0-255):" << std::endl;
              int motor = 0, intensity = 0;
              std::cerr << std::endl << "[M I] ";
              std::cin >> motor >> intensity;
              rv->Vibrate(motor, intensity);
            }
          else if (input[0] == 'h')
            {
              PrintHelp();
            }
          else if (input[0] == 'c')
            {
              std::cerr << "Enter the device manager you'd like to use:" << std::endl;
              std::cerr << "[DM] ";
              std::getline(std::cin, input);
              int err;
              if ((err = rv->ChangeDeviceManager(input)) != 0)
              {
                std::cerr << "Failed with code " << err << std::endl;
                goto prompt;
              }
              else
              {
                std::cerr << "Successfully changed manager" << std::endl;
              }
              if (rv->FindDevice())
              {
                std::cerr << "Bluetooth lookup failed, defaulting to TextManager" << std::endl;
                rv->ChangeDeviceManager("TextManager");
              }
            }
          else if (input[0] == 'l')
            {
              std::cerr << "Enter the integer corresponding to the log mode you want (0-4):" << std::endl;
              int log = 0;
              std::cerr << std::endl << "[L] ";
              std::cin >> log;
              rv->SetLogMode(log);
            }
        }
  prompt:
      GetInput(input);
    }
  delete rv;
  return 0;
}
