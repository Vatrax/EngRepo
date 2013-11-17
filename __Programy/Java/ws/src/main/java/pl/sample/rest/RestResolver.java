package pl.sample.rest;

import java.util.HashSet;
import java.util.Set;

import javax.ws.rs.ApplicationPath;
import javax.ws.rs.core.Application;

/**
 * @author: Wojciech Krzaczek
 */

@ApplicationPath("/rest")
public class RestResolver extends Application {
	@Override
	public Set<Class<?>> getClasses() {
		HashSet<Class<?>> serviceClasses = new HashSet<Class<?>>();
		serviceClasses.add(Rest.class);
		return serviceClasses;
	}
}
