#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::Throw;

#include <math.h>

#include "../SpaceBattle/Vector.h"
#include "../SpaceBattle/IFuelUsing.h"
#include "../SpaceBattle/IMovable.h"
#include "../SpaceBattle/IMoveWithRotation.h"
#include "../SpaceBattle/Commands/ICommand.h"
#include "../SpaceBattle/Commands/CheckFuelCommand.h"
#include "../SpaceBattle/Commands/BurnFuelCommand.h"
#include "../SpaceBattle/Commands/MacroCommand.h"
#include "../SpaceBattle/Commands/MoveCommand.h"
#include "../SpaceBattle/Commands/RotateCommand.h"
#include "../SpaceBattle/Commands/UpdateVelocityCommand.h"
#include "../SpaceBattle/CommandException.h"

class CommandMock : public ICommand {
public:
	MOCK_METHOD((void), execute, (), (override));
	~CommandMock() override { Die(); }	// для проверки вызова деструктора
	MOCK_METHOD((void), Die, ());
};

class FuelUsingMock : public IFuelUsing {
public:
	MOCK_METHOD((unsigned int), getFuel, (), (override));
	MOCK_METHOD((void), setFuel, (unsigned int), (override));
	MOCK_METHOD((unsigned int), getFuelConsumption, (), (override));
};

class MovableMock : public IMovable {
public:
	MOCK_METHOD((const Vector*), getPosition, (), (override));
	MOCK_METHOD((void), setPosition, (const Vector&), (override));
	MOCK_METHOD((const Vector*), getVelocity, (), (override));
};

class MovableUsingFuelMock : public FuelUsingMock, public MovableMock {
public:

};

class MoveWithRotationMock :public IMoveWithRotation
{
public:
	MOCK_METHOD((const Vector*), getPosition, (), (override));
	MOCK_METHOD((void), setPosition, (const Vector&), (override));
	MOCK_METHOD((const Vector*), getVelocity, (), (override));
	MOCK_METHOD((void), setVelocity, (const Vector&), (override));
	MOCK_METHOD((const Angle*), getDirection, (), (override));
	MOCK_METHOD((void), setDirection, (const Angle&), (override));
	MOCK_METHOD((int), getAngularVelocity, (), (override));
};

//тесты CheckFuelComamnd
TEST(TestCheckFuelComamnd, CheckFuelComamnd_succeed)
{
	FuelUsingMock fuelUsingMock;
	CheckFuelCommand testCommand(&fuelUsingMock);

	EXPECT_CALL(fuelUsingMock, getFuel()).WillOnce(Return(((int) 10)));
	EXPECT_CALL(fuelUsingMock, getFuelConsumption()).WillOnce(Return((int) 9));

	EXPECT_NO_THROW({
		testCommand.execute();
		});
}

TEST(TestCheckFuelComamnd, CheckFuelComamnd_throw_exception)
{
	FuelUsingMock fuelUsingMock;
	CheckFuelCommand testCommand(&fuelUsingMock);

	EXPECT_CALL(fuelUsingMock, getFuel()).WillOnce(Return(((int)9)));
	EXPECT_CALL(fuelUsingMock, getFuelConsumption()).WillOnce(Return((int)10));

	EXPECT_THROW({
		testCommand.execute();
		}, CommandException*);
}

//тесты BurnFuelComamnd
TEST(TestBurnFuelComamnd, BurnFuelComamnd_succeed)
{
	FuelUsingMock fuelUsingMock;
	BurnFuelCommand testCommand(&fuelUsingMock);

	EXPECT_CALL(fuelUsingMock, getFuel()).WillOnce(Return(((int)10)));
	EXPECT_CALL(fuelUsingMock, getFuelConsumption()).WillOnce(Return((int)5));

	EXPECT_CALL(fuelUsingMock, setFuel(5)).Times(1);

	EXPECT_NO_THROW({
		testCommand.execute();
	});
}

// тесты макрокоманды

//Реализовать простейшую макрокоманду и тесты к ней. Здесь простейшая - это значит, 
//что при выбросе исключения вся последовательность команд приостанавливает свое выполнение, а макрокоманда выбрасывает CommandException.
TEST(TestMacroComamnd, MacroComamnd_succeed)
{
	CommandMock* commandsArr[] = { 
		new CommandMock(), 
		new CommandMock(), 
		new CommandMock() 
	};
	MacroCommand testCommand((ICommand**)commandsArr, std::size(commandsArr));

	EXPECT_CALL(*commandsArr[0], execute()).Times(1);
	EXPECT_CALL(*commandsArr[1], execute()).Times(1);
	EXPECT_CALL(*commandsArr[2], execute()).Times(1);

	//Проверка освобождения памяти динамически созданных объектов
	EXPECT_CALL(*commandsArr[0], Die()).Times(1);
	EXPECT_CALL(*commandsArr[1], Die()).Times(1);
	EXPECT_CALL(*commandsArr[2], Die()).Times(1);

	EXPECT_NO_THROW({
		testCommand.execute();
		});
}

TEST(TestMacroComamnd, MacroComamnd_abort_if_exception)
{
	CommandMock* commandsArr[] = {
		new CommandMock(),
		new CommandMock(),
		new CommandMock(),
		new CommandMock()
	};
	MacroCommand testCommand((ICommand**)commandsArr, std::size(commandsArr));

	EXPECT_CALL(*commandsArr[0], execute()).Times(1);
	EXPECT_CALL(*commandsArr[1], execute()).Times(1).WillOnce(Throw(new CommandException));
	EXPECT_CALL(*commandsArr[2], execute()).Times(0);
	EXPECT_CALL(*commandsArr[3], execute()).Times(0);

	//Проверка освобождения памяти динамически созданных объектов
	EXPECT_CALL(*commandsArr[0], Die()).Times(1);
	EXPECT_CALL(*commandsArr[1], Die()).Times(1);
	EXPECT_CALL(*commandsArr[2], Die()).Times(1);
	EXPECT_CALL(*commandsArr[3], Die()).Times(1);

	EXPECT_THROW({
		testCommand.execute();
		}, CommandException*);
}

// Реализовать команду движения по прямой с расходом топлива, используя команды с предыдущих шагов.
TEST(TestMoveFuelComamnd, Move_command_with_fuel_burn_succeed)
{
	MovableUsingFuelMock moveUseFuelMockObj;

	ICommand* commandsArr[] = {
		new CheckFuelCommand(&moveUseFuelMockObj),
		new MoveCommand(&moveUseFuelMockObj),
		new BurnFuelCommand(&moveUseFuelMockObj)
	};

	MacroCommand moveUseFuelCommand((ICommand**)commandsArr, std::size(commandsArr));

	// проверка и сжигание топлива
	EXPECT_CALL(moveUseFuelMockObj, getFuel()).Times(2).WillRepeatedly(Return((int)5));
	EXPECT_CALL(moveUseFuelMockObj, getFuelConsumption()).Times(2).WillRepeatedly(Return((int)3));
	EXPECT_CALL(moveUseFuelMockObj, setFuel(2)).Times(1);

	// движение
	Vector pos(12,5);
	Vector vel(-7, 3);
	EXPECT_CALL(moveUseFuelMockObj, getPosition()).WillOnce(Return(&pos));
	EXPECT_CALL(moveUseFuelMockObj, getVelocity()).WillOnce(Return(&vel));
	EXPECT_CALL(moveUseFuelMockObj, setPosition(Vector(5,8))).Times(1);

	EXPECT_NO_THROW({
		moveUseFuelCommand.execute();
		});
}

TEST(TestMoveFuelComamnd, Move_no_fuel_excemption)
{
	MovableUsingFuelMock moveUseFuelMockObj;

	ICommand* commandsArr[] = {
		new CheckFuelCommand(&moveUseFuelMockObj),
		new MoveCommand(&moveUseFuelMockObj),
		new BurnFuelCommand(&moveUseFuelMockObj)
	};

	MacroCommand moveUseFuelCommand((ICommand**)commandsArr, std::size(commandsArr));

	// проверка и сжигание топлива
	EXPECT_CALL(moveUseFuelMockObj, getFuel()).Times(1).WillRepeatedly(Return((int)0));
	EXPECT_CALL(moveUseFuelMockObj, getFuelConsumption()).Times(1).WillRepeatedly(Return((int)3));
	EXPECT_CALL(moveUseFuelMockObj, setFuel(testing::_)).Times(0);

	// движение
	EXPECT_CALL(moveUseFuelMockObj, getPosition()).Times(0);
	EXPECT_CALL(moveUseFuelMockObj, getVelocity()).Times(0);
	EXPECT_CALL(moveUseFuelMockObj, setPosition(testing::_)).Times(0);

	EXPECT_THROW({
		moveUseFuelCommand.execute();
		}, CommandException*);
}


// тест нахождения длины вектора
TEST(TestVector, calculate_vector_magnitude)
{
	// двумерный
	EXPECT_NEAR(Vector::calcMagnitude(Vector(0,0)), 0.0, std::numeric_limits<double>::epsilon());
	EXPECT_NEAR(Vector::calcMagnitude(Vector(3, 4)), 5.0, std::numeric_limits<double>::epsilon());
	EXPECT_NEAR(Vector::calcMagnitude(Vector(-1, -1)), sqrt(2.0), std::numeric_limits<double>::epsilon());

	//n-мерный
	int param[] = { 1,-1,1,-1 };
	EXPECT_NEAR(Vector::calcMagnitude(Vector(param, std::size(param))), 2.0, std::numeric_limits<double>::epsilon());
	
	int param2[] = {2500};
	EXPECT_NEAR(Vector::calcMagnitude(Vector(param2, std::size(param2))), 2500.0, std::numeric_limits<double>::epsilon());

}

//Реализовать команду для модификации вектора мгновенной скорости при повороте. 
// Необходимо учесть, что не каждый разворачивающийся объект движется.
TEST(TestUpdateVelocityCommand, update_velocity_command_succeed)
{
	MoveWithRotationMock moveRotationMockObj;
	UpdateVelocityCommand updateVelocityCommand(&moveRotationMockObj);
	Vector vel(-3, 4);	// модуль = 5
	Angle dir(30, 360);	// 30 градусов: sin = 1/2, cos = sqrt(3)/2

	EXPECT_CALL(moveRotationMockObj, getPosition()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setPosition(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getVelocity()).Times(1).WillOnce(Return(&vel));
	EXPECT_CALL(moveRotationMockObj, getDirection()).Times(1).WillOnce(Return(&dir));
	EXPECT_CALL(moveRotationMockObj, setDirection(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getAngularVelocity()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setVelocity(Vector((int)(sqrt(3)*5/2), (int)(5/2)))).Times(1);

	EXPECT_NO_THROW({
		updateVelocityCommand.execute();
		});
}

TEST(TestUpdateVelocityCommand, update_velocity_command_succeed2)
{
	MoveWithRotationMock moveRotationMockObj;
	UpdateVelocityCommand updateVelocityCommand(&moveRotationMockObj);
	Vector vel(5, -5);	// модуль = sqrt(50)
	Angle dir(270, 360);	// 270 градусов: sin = -1, cos 0

	EXPECT_CALL(moveRotationMockObj, getPosition()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setPosition(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getVelocity()).Times(1).WillOnce(Return(&vel));
	EXPECT_CALL(moveRotationMockObj, getDirection()).Times(1).WillOnce(Return(&dir));
	EXPECT_CALL(moveRotationMockObj, setDirection(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getAngularVelocity()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setVelocity(Vector(0, (int) - sqrt(50)))).Times(1);

	EXPECT_NO_THROW({
		updateVelocityCommand.execute();
		});
}

TEST(TestUpdateVelocityCommand, update_velocity_command_zero_speed)
{
	MoveWithRotationMock moveRotationMockObj;
	UpdateVelocityCommand updateVelocityCommand(&moveRotationMockObj);
	Vector vel(0, 0);		// модуль = 0)
	Angle dir(90, 360);		// 90 градусов: sin = 1, cos = 0

	EXPECT_CALL(moveRotationMockObj, getPosition()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setPosition(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getVelocity()).Times(1).WillOnce(Return(&vel));
	EXPECT_CALL(moveRotationMockObj, getDirection()).Times(1).WillOnce(Return(&dir));
	EXPECT_CALL(moveRotationMockObj, setDirection(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getAngularVelocity()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setVelocity(testing::_)).Times(0);

	EXPECT_NO_THROW({
		updateVelocityCommand.execute();
		});
}

// Реализовать команду поворота, которая еще и меняет вектор мгновенной скорости, если есть.
TEST(TestRotateUpdateVelocityCommand, rotate_update_velocity_command_succeed)
{
	MoveWithRotationMock moveRotationMockObj;

	ICommand* commandsArr[] = {
		new RotateCommand(&moveRotationMockObj),
		new UpdateVelocityCommand(&moveRotationMockObj),
	};

	MacroCommand rotateAndUpdateVelocityCommand((ICommand**)commandsArr, std::size(commandsArr));

	// (начальное состояние) =>	линейная скорость = (-1,-1), угол = 50 град., угловая скорость = -5 =>
	// (Rotation) => линейная скорость = (-1,-1), угол = 45 град., угловая скорость = -5 =>
	// (updateVelocity) => линейная скорость = (1,1), угол = 45 град., угловая скорость = -5
	Vector vel(-1, -1);		// модуль = sqrt(2))
	Angle dir_start(50, 360);		
	int ang_vel = -5; 
	Angle dir_end(45, 360); // 50-5 = 45 градусов: sin = sqrt(2)/2, cos = sqrt(2)/2
	
	EXPECT_CALL(moveRotationMockObj, getPosition()).Times(0);
	EXPECT_CALL(moveRotationMockObj, setPosition(testing::_)).Times(0);
	EXPECT_CALL(moveRotationMockObj, getVelocity()).Times(1).WillOnce(Return(&vel));
	EXPECT_CALL(moveRotationMockObj, getDirection()).Times(2).WillOnce(Return(&dir_start)).WillOnce(Return(&dir_end));
	EXPECT_CALL(moveRotationMockObj, setDirection(dir_end)).Times(1);
	EXPECT_CALL(moveRotationMockObj, getAngularVelocity()).WillOnce(Return(ang_vel));
	EXPECT_CALL(moveRotationMockObj, setVelocity(Vector(1, 1))).Times(1);

	EXPECT_NO_THROW({
		rotateAndUpdateVelocityCommand.execute();
		});
}