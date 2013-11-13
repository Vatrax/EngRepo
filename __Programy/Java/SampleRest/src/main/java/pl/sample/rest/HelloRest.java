package pl.sample.rest;

import java.io.Serializable;
import java.util.ArrayList;

import javax.annotation.PostConstruct;
import javax.enterprise.context.SessionScoped;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

/**
 * @author: Wojciech Krzaczek
 */

@Path("/first")
@SessionScoped
public class HelloRest implements Serializable {
	private static final long serialVersionUID = 7389094554784730821L;
	private ArrayList<Sector> sectorList;

	@PostConstruct
	public void setup() {
		sectorList = new ArrayList<Sector>();
		for (int i = 0; i < 100; i++) {
			sectorList.add(new Sector("Sample" + i, DeviceType.ACC, i));
		}
	}

	@GET
	@Path("/helloWorld")
	public String helloWorld() {
		return "Hello World";
	}

	@GET
	@Path("/user/{id}")
	public Response getUserById(@PathParam("id") int id) {
		if (id < 1 || id >= sectorList.size())
			return Response.status(Status.BAD_REQUEST)
					.entity("Nie znaleziono sektora o podanym id").build();
		return Response.ok(sectorList.get(id - 1))
				.type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/users/all")
	public Response getAllUser() {
		return Response.ok(sectorList).type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/users/add/{name}/{value}")
	public Response addGetUser(@PathParam("name") String name,
			@PathParam("value") int value) {
		sectorList.add(new Sector(name, DeviceType.LIGHT, value));
		return Response.status(200)
				.entity("addUser is called, name : " + name + " " + value)
				.build();

	}

	@POST
	@Path("/users/add")
	public Response addPostUser(@FormParam("name") String name,
			@FormParam("value") int value) {
		sectorList.add(new Sector(name, DeviceType.SHUTTERS, value));
		return Response.status(200)
				.entity("addUser is called, name : " + name + " " + value)
				.build();

	}
}
