#include <gtest/gtest.h>


#include "parking_system.hpp"

// Typical mapping: 1=big, 2=medium, 3=small.

TEST(ParkingSystemTest, SmallCarDecrementsAndEventuallyFails) {
    ParkingSystem ps(/*big=*/0, /*medium=*/0, /*small=*/2);

    EXPECT_TRUE(ps.addCar(3));
    EXPECT_TRUE(ps.addCar(3));
    EXPECT_FALSE(ps.addCar(3)); // no small slots left
}

TEST(ParkingSystemTest, MediumCarDecrementsAndEventuallyFails) {
    ParkingSystem ps(/*big=*/0, /*medium=*/1, /*small=*/0);

    EXPECT_TRUE(ps.addCar(2));
    EXPECT_FALSE(ps.addCar(2)); // no medium slots left
}

TEST(ParkingSystemTest, BigCarDecrementsAndEventuallyFails) {
    ParkingSystem ps(/*big=*/1, /*medium=*/0, /*small=*/0);

    // This test SHOULD pass for a correct implementation.
    // With your current code, it will FAIL because addCar(1) returns false.
    EXPECT_TRUE(ps.addCar(1));
    EXPECT_FALSE(ps.addCar(1)); // no big slots left
}

TEST(ParkingSystemTest, DifferentTypesDoNotAffectOtherSlots) {
    ParkingSystem ps(/*big=*/1, /*medium=*/1, /*small=*/1);

    EXPECT_TRUE(ps.addCar(3));  // consume small
    EXPECT_FALSE(ps.addCar(3)); // small exhausted

    EXPECT_TRUE(ps.addCar(2));  // consume medium
    EXPECT_FALSE(ps.addCar(2)); // medium exhausted

    // This should be true once, then false.
    // With your current code, first expectation fails.
    EXPECT_TRUE(ps.addCar(1));
    EXPECT_FALSE(ps.addCar(1));
}

TEST(ParkingSystemTest, InvalidCarTypeAlwaysReturnsFalseAndDoesNotChangeState) {
    ParkingSystem ps(/*big=*/1, /*medium=*/1, /*small=*/1);

    EXPECT_FALSE(ps.addCar(0));
    EXPECT_FALSE(ps.addCar(4));
    EXPECT_FALSE(ps.addCar(-1));

    // Slots should still be available if invalid types don't mutate state
    EXPECT_TRUE(ps.addCar(3));
    EXPECT_TRUE(ps.addCar(2));
    // This should be true if big handling is correct; with your current code it will fail.
    EXPECT_TRUE(ps.addCar(1));
}