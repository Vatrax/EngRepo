package pl.sample.rest;

import java.io.Serializable;

import javax.persistence.Entity;

/**
 * @author: Wojciech Krzaczek
 */

@Entity
public class Sector implements Serializable {

	private static final long serialVersionUID = 6735425914919709308L;

	private long id;
	private String name;
	private DeviceType devicesType;
	private int value;

	public Sector(String name, DeviceType devicesType, int value) {
		super();
		this.name = name;
		this.devicesType = devicesType;
		this.value = value;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public DeviceType getDevicesType() {
		return devicesType;
	}

	public void setDevicesType(DeviceType devicesType) {
		this.devicesType = devicesType;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public long getId() {
		return id;
	}

}
