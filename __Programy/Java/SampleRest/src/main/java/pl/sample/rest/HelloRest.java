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

@Path("/first")
@SessionScoped
// <<- ta adnotacja tylko po to aby trzymać w sesji userList, jak nie potrzeba
// trzymać nic w sesji to nie potrzebna jest ta adnotacja
public class HelloRest implements Serializable {
	private static final long serialVersionUID = 7389094554784730821L;
	private ArrayList<User> userList;

	@PostConstruct
	// <- po utworzeniu się serwisu inicjowana jest nasza pseudo baza danych
	public void setup() {
		userList = new ArrayList<User>();
		for (int i = 0; i < 100; i++) {
			userList.add(new User("Sample" + i, "User" + i));
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
		if (id < 1 || id > userList.size())
			return Response.status(Status.BAD_REQUEST)
					.entity("Nie znaleziono uzytkownika o podanym id").build();
		return Response.ok(userList.get(id - 1))
				.type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/users/all")
	public Response getAllUser() {
		return Response.ok(userList).type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/users/add/{name}/{surname}")
	public Response addGetUser(@PathParam("name") String name,
			@PathParam("surname") String surname) {
		userList.add(new User(name, surname));
		return Response.status(200)
				.entity("addUser is called, name : " + name + " " + surname)
				.build();

	}
	@POST
	@Path("/users/add")
	public Response addPostUser(@FormParam("name") String name,
			@FormParam("surname") String surname) {
		userList.add(new User(name, surname));
		return Response.status(200)
				.entity("addUser is called, name : " + name + " " + surname)
				.build();

	}
}
