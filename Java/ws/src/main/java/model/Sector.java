package model;

import java.io.Serializable;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

/**
 * @author: Wojciech Krzaczek
 */

@Document(collection = "sectors")
public class Sector implements Serializable {

	private static final long serialVersionUID = 6735425914919709308L;

	@Id private String id;
	private String name;
	private DeviceType deviceType;
	private int value;

	public Sector() {
	}

	public Sector(String name, DeviceType deviceType, int value) {
		this.name = name;
		this.deviceType = deviceType;
		this.value = value;
	}

	public Sector(String id, String name, DeviceType dt, int value) {
		this(name, dt, value);
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public DeviceType getDeviceType() {
		return deviceType;
	}

	public void setDeviceType(DeviceType deviceType) {
		this.deviceType = deviceType;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public String getId() {
		return id;
	}

}
