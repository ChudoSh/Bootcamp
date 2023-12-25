import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import javax.servlet.http.HttpServletRequest;

@WebListener
public class Listener implements ServletContextListener{
	public Listener() {

	}

	@Override
	public void contextInitialized(ServletContextEvent sce) {
		ServletContext context = sce.getServletContext();
		try {
			// Create an instance of WebsiteController and store it as an attribute in the
			// servlet context
			AdminSQLManager adminSQLManager = new AdminSQLManager("adminDB");
			context.setAttribute("adminDB", adminSQLManager);
		} catch (Exception e) {
        // Log or handle the exception appropriately
        e.printStackTrace();
		}
	}

	@Override
	public void contextDestroyed(ServletContextEvent sce) {
		// Perform cleanup if needed
	}

	public static JsonObject HttpRecToJson(HttpServletRequest request) throws IOException {
		// Assuming that the data is in the form of URL-encoded parameters
		String companyName = request.getParameter("company_name");
		String productName = request.getParameter("product_name");
		String productDescription = request.getParameter("product_description");

		// Create a JSON object manually based on the retrieved parameters
		JsonObjectBuilder jsonObjectBuilder = Json.createObjectBuilder().add("company_name", companyName)
				.add("product_name", productName).add("product_description", productDescription);

		JsonObject jsonObject = jsonObjectBuilder.build();

		return jsonObject;
	}

	public static boolean isValid(JsonObject data, String[] keys) {
		for (String key : keys) {
			if (!data.containsKey(key)) {
				return false;
			}
		}

		return true;
	}

	public static JsonObject sendToGateway(JsonObject req) {
		try {
			// Create a SocketChannel object.
			try (SocketChannel socketChannel = SocketChannel.open()) {
				// Connect the SocketChannel to the server.
				InetSocketAddress serverAddress = new InetSocketAddress("localhost", 8080);
				socketChannel.connect(serverAddress);

				// Send the request as a JSON string
				socketChannel.write(ByteBuffer.wrap(req.toString().getBytes()));

				// Receive the response
				ByteBuffer buffer = ByteBuffer.allocate(1500);
				socketChannel.read(buffer);
				buffer.flip();

				// Convert the response to a JsonObject
				String jsonResponse = new String(buffer.array(), 0, buffer.limit());
				JsonObject responseObject = convertJsonStringToJsonObject(jsonResponse);

				return responseObject;
			}
		} catch (IOException e) {
			e.printStackTrace();
			return null; // or throw an exception if needed
		}
	}

	private static JsonObject convertJsonStringToJsonObject(String jsonString) {
		try (JsonReader reader = Json.createReader(new java.io.StringReader(jsonString))) {
			return reader.readObject();
		} catch (Exception e) {
			e.printStackTrace();
			// Handle the exception appropriately
			return null; // or throw an exception if needed
		}
	}
}
