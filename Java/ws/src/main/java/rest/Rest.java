package rest;

import model.DeviceType;
import model.Sector;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.ArrayList;
import java.util.List;

/**
 * @author: Wojciech Krzaczek
 */

@Path("/sector") public class Rest {

	private static List<Sector> sectors = new ArrayList<Sector>();
	private static int id = 0;

	@GET @Path("/byid/{id}") public Response getSectorById(@PathParam("id") String id) {
		Sector responseSector = null;
		for (Sector sector : sectors) {
			if (sector.getId().equals(id)) {
				responseSector = sector;
			}
		}

		return Response.ok(responseSector).type(MediaType.APPLICATION_JSON).build();
	}

	@GET @Path("/all") public Response getAllSectors() {
		return Response.ok(sectors).type(MediaType.APPLICATION_JSON).build();
	}

	@GET @Path("/byDT/{DT}") public Response getDeviceSectors(@PathParam("DT") String DT) {
		ArrayList<Sector> sectorsResponse = new ArrayList<Sector>();
		for (Sector sector : sectors) {
			if (sector.getDeviceType().equals(DeviceType.valueOf(DT))) {
				sectorsResponse.add(sector);
			}
		}
		return Response.ok(sectorsResponse).type(MediaType.APPLICATION_JSON).build();
	}

	@GET @Path("/update/{id}/{value}") public Response updateSector(@PathParam("id") String id,
			@PathParam("value") int value) {
		for (Sector sector : sectors) {
			if (sector.getId().equals(id)) {
				sector.setValue(value);
			}
		}
		return Response.ok("ok").build();
	}

	@GET @Path("/add/{name}/{DT}/{value}") public Response addSector(@PathParam("name") String name,
			@PathParam("DT") DeviceType dt, @PathParam("value") int value) {
		sectors.add(new Sector("" +id++, name, dt, value));
		return Response.ok("ok").build();
	}

}
