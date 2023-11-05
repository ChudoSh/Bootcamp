//package hello_world;
//
//import javax.servlet.*;
//import javax.servlet.http.*;
//
//import java.io.IOException;
//import java.io.PrintWriter;
//
//public class HelloWorld extends HttpServlet {
//    public void doGet(HttpServletRequest request, HttpServletResponse response)
//            throws IOException {
//        String name = request.getParameter("name");
//
//        // Set the content type to HTML
//        response.setContentType("text/html");
//
//        // Create an HTML response
//        response.getWriter().println("<html><body>");
//        if (name != null) {
//            response.getWriter().println("Hello " + name + "!");
//        } else {
//            response.getWriter().println("Hello World!");
//        }
//        response.getWriter().println("</body></html>");
//    }
//}