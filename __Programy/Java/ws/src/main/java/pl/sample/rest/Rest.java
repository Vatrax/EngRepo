package pl.sample.rest;

import java.io.Serializable;
import java.net.UnknownHostException;

import javax.annotation.PostConstruct;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.Response;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.data.mongodb.core.MongoOperations;

import com.mongodb.MongoClient;

/**
 * @author: Wojciech Krzaczek
 */

@Path("/first")
public class Rest implements Serializable {
	private static final long serialVersionUID = 7389094554784730821L;
	MongoClient mongo;
	private MongoOperations mongoOperation;
	private ApplicationContext ctx;

	@PostConstruct
	public void setup() throws UnknownHostException {
		ctx = new AnnotationConfigApplicationContext(SpringMongoConfig.class);
		mongoOperation = (MongoOperations) ctx.getBean("mongoTemplate");
		mongoOperation.save(new Sector("sample1", DeviceType.LIGHT, 100));
		mongoOperation.save(new Sector("sample2", DeviceType.ACC, 50));
		mongoOperation.save(new Sector("sample3", DeviceType.SHUTTERS, 0));
	}

	@GET
	@Path("/sector/{id}")
	public Response getSectorById(@PathParam("id") int id) {
		return Response.ok().build();
	}

	@GET
	@Path("/sector/all")
	public Response getAllSector() {
		return Response.ok().build();
	}

	@POST
	@Path("/sector/add")
	public Response addPostSector(@FormParam("id") long id) {
		return Response.ok().build();
	}

}
