package com.example.krzaczek.calculator.startedy;

/**
 * Created by krzaczek on 13.03.15.
 */
public class AddStrategy implements CalculationStrategy {
    @Override
    public double execute(double a, double b) {
        return a + b;
    }
}
