# CMakeList.txt: проект CMake для SpaceBattle; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

add_library(SpaceBattle STATIC
    
   
  "Angle.cpp" "Angle.h"
  "Vector.cpp" "Vector.h"
  
  "IMovable.h"
  "IRotatable.h"
  "IFuelUsing.h"
  "IMoveWithRotation.h"
  "Commands/ICommand.h" 
  "CommandException.h" "CommandException.cpp"  
  "Commands/MoveCommand.cpp" "Commands/MoveCommand.h"
  "Commands/RotateCommand.cpp" "Commands/RotateCommand.h"
  "Commands/CheckFuelCommand.cpp" "Commands/CheckFuelCommand.h"    
  "Commands/BurnFuelCommand.cpp" "Commands/BurnFuelCommand.h" 
  "Commands/MacroCommand.h" "Commands/MacroCommand.cpp" 
  "Commands/UpdateVelocityCommand.cpp" "Commands/UpdateVelocityCommand.h" )


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SpaceBattle PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
