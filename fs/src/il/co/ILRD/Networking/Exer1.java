package il.co.ILRD.Networking;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.Buffer;
import java.util.Optional;

public class Exer1 {
    public static void downloadWebpage(String urlName) throws IOException {
        URL downloadURL = new URL(urlName);
        BufferedReader reader = new BufferedReader(new InputStreamReader(downloadURL.openStream()));
        BufferedWriter writer = new BufferedWriter(new FileWriter("downloadedpage.html"));

        String line;
        while (null != (line = reader.readLine())) {
            writer.write(line);
        }

        reader.close();
        writer.close();
        System.out.println("Page downloaded");
    }

    public static void main(String[] args) throws IOException {
       Exer1.downloadWebpage("https://www.geeksforgeeks.org/download-web-page-using-java/");
    }
}
