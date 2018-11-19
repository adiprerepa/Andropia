import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class SimpleFileClient {

  //Lets just put some important variables here 
  //and forget about scope 
  //You can change these: 
  //Thinking about adding some I/O 
  //functionality
  public final static int SOCKET_PORT = 55555;
  public final static String SERVER_IP = "54.215.224.36";
  
  public final static String FILE_LOCATION_RECIEVED = "/home/aditya/RESULTS.txt/";
  //My stupid ass forgot about
  //The slash in front of home
  //*facepalm*
  public final static int FILE_SIZE = 6022386;

  public static void main (String [] args ) throws IOException {
    int bytesRead;
    int current = 0;
    FileOutputStream fos = null;
    BufferedOutputStream bos = null;
    Socket sock = null;
    try {
      sock = new Socket(SERVER_IP, SOCKET_PORT);
      /*
       * Try to connect to our server with the parameters of
       * the IPv4 of the Server and the Port that is 
       * ALLOWED on the server. In this case, 55555 because why not.
       * This is in a try block, means there could be an error
       * in connecting.
       * 
       */
      System.out.println("Connecting...");
      //Connection message//
      byte [] mybytearray  = new byte [FILE_SIZE];
      //
      InputStream is = sock.getInputStream();
      fos = new FileOutputStream(FILE_LOCATION_RECIEVED);
      bos = new BufferedOutputStream(fos);
      bytesRead = is.read(mybytearray,0,mybytearray.length);
      current = bytesRead;

      do {
         bytesRead =is.read(mybytearray, current, (mybytearray.length-current));
         if(bytesRead >= 0) current += bytesRead;
      } while(bytesRead > -1);

      bos.write(mybytearray, 0 , current);
      bos.flush();
      System.out.println("File " + FILE_LOCATION_RECIEVED
          + " downloaded (" + current + " bytes read)");
    }
    finally {
      if (fos != null) fos.close();
      if (bos != null) bos.close();
      if (sock != null) sock.close();
    }
  }

}

