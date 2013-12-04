package com.example.smartbuilding.model;

import java.io.Serializable;

/**
 * Created by Wojciech Krzaczek
 */

public class Sector implements Serializable{

    private String id;
    private String groupName;
    private DeviceType deviceType;
    private int value;

    public Sector() {}

    public Sector(String id, String groupName, DeviceType deviceType, int value) {
        this.id=id;
        this.groupName=groupName;
        this.deviceType=deviceType;
        this.value=value;

    }

    public String getId() {
        return id;
    }

    public String getGroupName() {
        return groupName;
    }

    public DeviceType getDeviceType() {
        return deviceType;
    }

    public int getValue() {
        return value;
    }

    public void setGroupName(String groupName) {
        this.groupName=groupName;
    }

    public void setDeviceType(DeviceType deviceType) {
        this.deviceType=deviceType;
    }

    public void setValue(int value) {
        this.value=value;
    }
}
