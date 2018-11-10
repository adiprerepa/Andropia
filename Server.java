import java.io.*;
import java.util.*;
import java.net.*;

public class Server {

    // Vector to store active clients 
    static Vector<ClientHandler> AllOfDaClients = new Vector<>();

    // counter for clients. Akshay you are very poopy.
    static int counter_for_clients = 0;

    public static void main(String[] args) throws IOException {
        // server is listening on port 56666
        String portNumberAsAString = args[1];
        runServer(portNumberAsAString);

        if(args[0] == null) {
            System.out.println("BITCH. USAGE : java Server <port-number> Get ur act together Aditya");
            System.exit(1);

        }
    }

    private static void runServer(String portNumberAsAString) throws IOException {
        Integer portNumber = Integer.parseInt(portNumberAsAString);
        ServerSocket ss = new ServerSocket(portNumber);

        Socket s;

        // running infinite loop for getting
        // client request
        // This is definitely it, Chief.
        while (true) {
            // Accept the incoming request
            s = ss.accept();
            // Whole Lotta Magic going on right now. Its hella dope ook?
            // So basically, The client socket is accepting from an API
            // inside the server socket class. Hella deep shit.
            // I want to marry the developers of the java.net package.

            System.out.println("New client request received : " + s);
            // This is lit. Lit af. That feeling when you get the new client
            // in your server. It's like getting married.

            // obtain input and output streams
            DataInputStream dataInputStream = new DataInputStream(s.getInputStream());
            DataOutputStream dataOutputStream = new DataOutputStream(s.getOutputStream());

            System.out.println("Creating a new handler for this client...");

            // Create a new handler object for handling this request.
            ClientHandler mtch = new ClientHandler(s, "client " + counter_for_clients, dataInputStream, dataOutputStream);

            // Create a new Thread with this object.
            Thread t = new Thread(mtch);

            System.out.println("Adding this client to active client list");

            // add this client to active clients list
            AllOfDaClients.add(mtch);

            // start the thread.
            t.start();

            // increment i for new client.
            // i is used for naming only, and can be replaced
            // by any naming scheme
            counter_for_clients++;
            // We should probably get a better naming scheme...
            // :)
        }

    }






} 
