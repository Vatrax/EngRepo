package pl.sample.rest;

import java.io.Serializable;
import java.net.UnknownHostException;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.data.mongodb.core.MongoOperations;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;

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
	}

	@GET
	@Path("/sector/byid/{id}")
	public Response getSectorById(@PathParam("id") String id) {
		Query query = new Query();
		query.addCriteria(Criteria.where("id").is(id));

		Sector sector = mongoOperation.findOne(query, Sector.class);
		return Response.ok(sector).type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/sector/all")
	public Response getAllSector() {
		List<Sector> list = mongoOperation.findAll(Sector.class);
		return Response.ok(list).type(MediaType.APPLICATION_JSON).build();
	}

	@GET
	@Path("/sector/byDT/{DT}")
	public Response getDeviceSector(@PathParam("DT") String DT) {
		Query query = new Query();
		query.addCriteria(Criteria.where("devicesType").is(DT));

		List<Sector> list = mongoOperation.find(query, Sector.class);
		return Response.ok(list).type(MediaType.APPLICATION_JSON).build();
	}

	@POST
	@Path("/sector/update")
	public Response addPostSector(@FormParam("id") String id,
			@FormParam("value") int value) {
		Query query = new Query();
		query.addCriteria(Criteria.where("id").is(id));

		Sector sector = mongoOperation.findOne(query, Sector.class);
		sector.setValue(value);
		mongoOperation.save(sector);

		return Response.ok(sector).build();
	}

	@GET
	@Path("/sector/add/{name}/{DT}/{value}")
	public Response addSector(@PathParam("name") String name,
			@PathParam("DT") DeviceType dt, @PathParam("value") int value) {
		mongoOperation.save(new Sector(name, dt, value));
		return Response.ok().type(MediaType.APPLICATION_JSON).build();
	}

}
