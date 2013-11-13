package com.example.smartbuilding.utils;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;

public class HttpFridgeService {
	
	private String token;
	private static String URL_LOGIN = "http://www.pawelszczerbicki.pl/smart-fridge/ws/login";
	private static String MSG_ERROR = "error";
	
	
	public boolean login(String username, String password){

		List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>();
		nameValuePairs.add(new BasicNameValuePair("login", username));
        nameValuePairs.add(new BasicNameValuePair("password", password));
        String reponse = ConnectionService.post(nameValuePairs, URL_LOGIN, false);
        token = !reponse.equals(MSG_ERROR) ? reponse : null;  
        return token==null?false:true;
		
		
	}
}
