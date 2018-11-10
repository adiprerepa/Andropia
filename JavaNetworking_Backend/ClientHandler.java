import java.io.*;
import java.util.*;
import java.net.*;

public class ClientHandler implements Runnable  {
    private String name;
    DataInputStream dataInputStreamBoi;
    DataOutputStream dataOutputStreamBoi;
    Socket socket;
    boolean isloggedin;

    // constructor : I use way too many external classes :)
    public ClientHandler(Socket socket, String name, DataInputStream dataInputStreamBoi, DataOutputStream dataOutputStreamBoi) {
        this.dataInputStreamBoi = dataInputStreamBoi;
        this.dataOutputStreamBoi = dataOutputStreamBoi;
        this.name = name;
        this.socket = socket;
        this.isloggedin = true;

        //Intellij's internal generate methods make life alot easier.
        //This shit generated the constructor for you.
    }

    @Override
    // I got errors, I think there is a run() in Runnable, I might be stupid
    public void run() {

        String received;
        while (true) {
            try {
                // receive the string 
                received = dataInputStreamBoi.readUTF();

                System.out.println(received);

                if(received.equals("logout")){
                    this.isloggedin=false;
                    this.socket.close();
                    break;
                }

                // break the string into message and recipient part 
                StringTokenizer st = new StringTokenizer(received, "#");
                // StringTokenizer. It needs to be killed, Oracle.
                String MsgToSend = st.nextToken();
                String recipient = st.nextToken();

                // search for the recipient in the connected devices list. 
                // ar is the vector storing client of active users
                // Is Aditya smart or what
                for (ClientHandler mc : Server.AllOfDaClients)
                {
                    // if the recipient is found, write on its 
                    // output stream...
                    if (mc.name.equals(recipient) && mc.isloggedin==true)
                    {
                        mc.dataOutputStreamBoi.writeUTF(this.name+" : "+MsgToSend);
                        break;
                    }
                }
            } catch (IOException e) {

                e.printStackTrace();
            }

        }
        try
        {
            // closing resources 
            this.dataInputStreamBoi.close();
            this.dataOutputStreamBoi.close();

        }catch(IOException e){
            e.printStackTrace();
        }
    }
} 
