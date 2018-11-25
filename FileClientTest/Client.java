import java.io.*;
import java.util.*;
import java.net.*;

public class Client {

    public static void main(String[] args) throws IOException {
        File readFile = new File("/Users/aku/test/thisIsATest.txt");

        BufferedReader br = new BufferedReader(new FileReader(readFile));

        ArrayList<String> readLines = new ArrayList<>();
        String st;
        String allContents;
        Socket socket = null;
        while ((st = br.readLine()) != null) {
            readLines.add(st);

        }
        ObjectOutputStream os = null;
        try {
            socket = new Socket(args[0], Integer.parseInt(args[1]));
        }
        catch (Exception ec) {
            System.out.println("Error connecting to server...Better luck next time.");
        }

        System.out.println("Connection Accepted on host 54.215.224.36 with port 55555..");

        try {
            //assert socket != null;
            os = new ObjectOutputStream(socket.getOutputStream());
        }catch (Exception e) {
            System.out.println("Error getting input stream.");
        }
        allContents = String.join(". ", readLines);
        assert os != null;
        os.writeObject(allContents);


    }
}
