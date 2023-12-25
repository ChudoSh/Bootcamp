

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import javax.json.stream.JsonParsingException;
import javax.json.Json;

@WebServlet("/company")
public class Company extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private AdminSQLManager adminSQLManager; 
	
	@Override
	public void init(ServletConfig config) throws ServletException {
		ServletContext context = config.getServletContext();
		adminSQLManager = (AdminSQLManager) context.getAttribute("adminDB");
		
		if (null == adminSQLManager) {
			throw new  ServletException("Yikes, db not found");
		}
        
	}
	
	@Override
	protected void doPost(HttpServletRequest request, 
			HttpServletResponse response) throws IOException {

	        // Check the content type
	        if ("application/x-www-form-urlencoded".equals(request.getContentType())) {
	            // Parse the form data into a JSON object
	            Map<String, String> formData = parseFormUrlEncodedToJson(request.getReader().lines().collect(Collectors.joining()));
	            JsonObject json = convertMapToJson(formData);

	            try {
	                // Register the company using the adminSQLManager
	                this.adminSQLManager.registerCompany(json);
	                response.setContentType("text/plain");
	                try (PrintWriter out = response.getWriter()) {
	                    out.print("Company registered successfully!");
	                }
	            } catch (RuntimeException e) {
	                // Log the exception or send an error response
	                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
	                response.setContentType("text/plain");
	                try (PrintWriter out = response.getWriter()) {
	                    out.print("Error registering the company: " + e.getMessage());
	                }
	            }
	        } else {
	            // If the content type is not "application/x-www-form-urlencoded", handle accordingly
	            response.setStatus(HttpServletResponse.SC_UNSUPPORTED_MEDIA_TYPE);
	            response.setContentType("text/plain");
	            try (PrintWriter out = response.getWriter()) {
	                out.print("Unsupported media type: " + request.getContentType());
	            }
	        }
	}
	
	private Map<String, String> parseFormUrlEncodedToJson(String formData) {
        Map<String, String> jsonMap = new HashMap<>();

        try {
            String[] pairs = formData.split("&");

            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                String key = URLDecoder.decode(keyValue[0], "UTF-8");
                String value = URLDecoder.decode(keyValue[1], "UTF-8");
                jsonMap.put(key, value);
            }

        } catch (IOException e) {
            e.printStackTrace(); // Handle the exception according to your needs
        }

        return jsonMap;
    }
	
	private JsonObject convertMapToJson(Map<String, String> formData) {
        JsonObjectBuilder jsonBuilder = Json.createObjectBuilder();

        for (Map.Entry<String, String> entry : formData.entrySet()) {
            jsonBuilder.add(entry.getKey(), entry.getValue());
        }

        return jsonBuilder.build();
    }
	

}
