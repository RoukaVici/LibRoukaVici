#include <iostream>
#include "RoukaVici.hh"

void PrintHelp()
{
  std::cout << "Commands:" << std::endl;
  std::cout << "v: Send a vibration" << std::endl;
  std::cout << "c: Change Device Manager" << std::endl;
  std::cout << "l: Change Log Method" << std::endl;
  std::cout << "h: Print this help message" << std::endl;
  std::cout << "q: Quit this program" << std::endl;
}

void  GetInput(std::string& input)
{
  std::cout << "<RV> ";
  std::getline(std::cin, input);
  while (input[0] == 0)
  {
    std::getline(std::cin, input);
  }
}

int main() {
  RoukaVici *rv = new RoukaVici();  // Initialize the library

  std::cout << "Welcome to the RoukaVici interactive command line" << std::endl;
  std::cout << "This program will let you interact with your glove using a very barebones command list" << std::endl << std::endl;
  PrintHelp();

  std::string input;
  GetInput(input);
  while (input != "q")
    {
      if (input.length() > 0)
        {
          if (input[0] == 'v')
            {
              std::cout << "Enter motor number M and intensity I (0-255):" << std::endl;
              int motor = 0, intensity = 0;
              std::cout << std::endl << "[M I] ";
              std::cin >> motor >> intensity;
              rv->Vibrate(motor, intensity);
            }
          else if (input[0] == 'h')
            {
              PrintHelp();
            }
          else if (input[0] == 'c')
            {
              std::cout << "Enter the device manager you'd like to use:" << std::endl;
              std::cout << "[DM] ";
              std::getline(std::cin, input);
              rv->ChangeDeviceManager(input);
              if (rv->FindDevice())
                {
                  std::cout << "Bluetooth lookup failed, defaulting to TextManager" << std::endl;
                  rv->ChangeDeviceManager("TextManager");
                }
            }
          else if (input[0] == 'l')
            {
              std::cout << "Enter the integer corresponding to the log mode you want (0-4):" << std::endl;
              int log = 0;
              std::cout << std::endl << "[L] ";
              std::cin >> log;
              rv->SetLogMode(log);
            }
        }
      GetInput(input);
    }
  delete rv;
  return 0;
}
