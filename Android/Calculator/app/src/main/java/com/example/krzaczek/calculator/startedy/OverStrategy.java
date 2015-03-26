package com.example.krzaczek.calculator.startedy;

/**
 * Created by krzaczek on 13.03.15.
 */
public class OverStrategy implements CalculationStrategy {
    @Override
    public double execute(double a, double b) {
        return 1 / a;
    }
}
