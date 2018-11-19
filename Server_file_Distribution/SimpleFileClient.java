import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class SimpleFileClient {
  
  public final static int FILE_SIZE = 6022386;

  public static void main (String [] args ) throws IOException {
    int bytesRead;
    int current = 0;

    FileOutputStream fos = null;
    BufferedOutputStream bos = null;
    Socket sock = null;

    Scanner sc = new Scanner(System.in);

    System.out.println("Enter the Ipv4 of your server : ");
    String SERVER_IP = sc.nextLine();

    System.out.println("Enter the ALLOWED port of the server that you would like to connect to : ");
    int SOCKET_PORT = sc.nextInt();

    System.out.println("Enter the path of the file of which you would like the file recieved to be saved : ");
    sc.nextLine();
    String FILE_LOCATION_RECIEVED = sc.nextLine();
    //sc.nextLine();
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
      //This creates a SENDABLE byteArray that the Client will recieve!

      InputStream is = sock.getInputStream();
      //Magic happens here, because the Stream being
      //Recieved is the File itself. Another
      //API maybe?

      fos = new FileOutputStream(FILE_LOCATION_RECIEVED);
      //Where the stuff recieved from the server will be spit out.
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
      if (sc != null) sc.close();
    }
  }

}


