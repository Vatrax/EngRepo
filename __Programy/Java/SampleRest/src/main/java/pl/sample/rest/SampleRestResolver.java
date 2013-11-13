package pl.sample.rest;

import java.util.HashSet;
import java.util.Set;

import javax.ejb.Stateless;
import javax.ws.rs.ApplicationPath;
import javax.ws.rs.core.Application;

/**
 * @author: Wojciech Krzaczek
 */

@Stateless
@ApplicationPath("/rest")
public class SampleRestResolver extends Application {
	@Override
	public Set<Class<?>> getClasses() {
		HashSet<Class<?>> serviceClasses = new HashSet<Class<?>>();
		serviceClasses.add(HelloRest.class);
		return serviceClasses;
	}
}
