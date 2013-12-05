package com.example.smartbuilding.model;

import java.io.Serializable;

/**
 * Created by Wojciech Krzaczek
 */

public class Sector implements Serializable {

    private String id;
    private String name;
    private DeviceType deviceType;
    private int value;

    public Sector() {
    }

    public Sector(String id, String name, DeviceType deviceType, int value) {
        this.id = id;
        this.name = name;
        this.deviceType = deviceType;
        this.value = value;

    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public DeviceType getDeviceType() {
        return deviceType;
    }

    public int getValue() {
        return value;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDeviceType(DeviceType deviceType) {
        this.deviceType = deviceType;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
