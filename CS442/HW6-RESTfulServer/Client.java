import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.util.regex.*;
import java.util.*;

public class Client extends java.applet.Applet implements MouseListener, Runnable {
	private final String X = "X";
	private final String O = "O";
	private final String WIN = "WIN";
	private final String TIE = "CAT'S GAME";
	private final String LOSE = "LOSE";
	
	private boolean gameIsDone = false;
	private String gameResult = "";
	private Rectangle[] cells = new Rectangle[9];
	private String[] boardTokens = new String[9];
	private String token = null;
	private HTTPRequest request = null;

	public void init() {
		addMouseListener(this);
		
		request = new HTTPRequest("http://localhost:8080");
		this.token = this.retriveMyToken();
		
		Thread updateThread = new Thread(this);
		updateThread.start();
	}

	public void paint(Graphics g) {
		g.setFont(new Font("Arial", Font.BOLD, 40));
		int fontX = 100;
		int fontY = 125;
		
		this.drawBoard(g);
		
		if (!this.canPlayGame()) {
			g.drawString("Game is full.", fontX, fontY);
			return;
		}
		
		// get board values from server
		this.boardTokens = this.retrieveBoardTokens();
		
		// draw all the X's and O's
		for (int i = 0; i < this.boardTokens.length; i++)
			if (this.boardTokens[i].equals(X))
				this.drawX(g, this.cells[i]);
			else if (this.boardTokens[i].equals(O))
				this.drawO(g, this.cells[i]);
		
		// draw game result if the game is over
		if (this.gameIsDone) {
			switch (this.gameResult) {
				case WIN:
					g.setColor(Color.GREEN);
					break;
				case TIE:
					g.setColor(Color.BLACK);
					break;
				case LOSE:
					g.setColor(Color.RED);
					break;
				default:
					System.out.println("Invalid gameResult.");
			}
			g.drawString(this.gameResult, fontX, fontY);
		}
	}
	
	public void run() {
		try {
			while (true) {
				if (!this.gameIsDone) {
					this.getNewData();
					Thread.sleep(1000);
				}
			}
		} catch(Exception x) {
			x.printStackTrace();
		}
	}
	
	public void mousePressed(MouseEvent e) {
		if (!this.canPlayGame())
			return;
		
		int mouseX = e.getX();
		int mouseY = e.getY();
		
		int index = this.cellIndexFromPoint(mouseX, mouseY);
		if (index != -1 && !this.gameIsDone)
			if (this.boardTokens[index].equals("")) // if the cell is empty
				this.sendToken(index, this.token);
		
		if (!this.gameIsDone)
			repaint();
	}
	
	public void mouseClicked(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	
	public void getNewData() {
		// if the game is done set the game result
		if (this.isGameDone()) {
			String winner = this.retrieveWinner();
			this.gameIsDone = true;
			if (winner.equals(this.token))
				this.gameResult = WIN;
			else if (winner.equals("None"))
				this.gameResult = TIE;
			else
				this.gameResult = LOSE;
		}
		repaint();
	}
	
	/* HTTP Request Methods */
	
	private String retriveMyToken() {
		return this.parseJSONKey(request.get("/available_token/"), "token");
	}
	
	private String[] retrieveBoardTokens() {
		String[] result = this.boardTokens;
		String json = request.get("/tokens/get/");
		for (int i = 0; i < this.boardTokens.length; i++)
			result[i] = this.parseJSONKey(json, Integer.toString(i));
		return result;
	}
	
	private String retrieveWinner() {
		String json = request.get("/get_winner/");
		String result = this.parseJSONKey(request.get("/get_winner/"), "winner");
		return result;
	}
	
	private void sendToken(int index, String token) {
		request.put("/tokens/put/", String.format("key=%s&value=%s", index, token));
	}
	
	private boolean isGameDone() {
		if (this.gameIsDone)
			return true;
		this.gameIsDone = (this.retrieveWinner().length() > 0);
		return this.gameIsDone;
	}
	
	private String parseJSONKey(String json, String key) {
		Matcher m = Pattern.compile("\"" + key + "\": \"([^\"]*)").matcher(json);
		if (m.find())
			return m.group(1);
		return "";
	}
	
	private int cellIndexFromPoint(int x, int y) {
		for (int i = 0; i < this.cells.length; i++)
			if (this.cells[i].contains(x, y))
				return i;
		return -1;
	}
	
	private void drawBoard(Graphics g) {
		g.setColor(Color.BLUE);
		g.drawString("Tic Tac Toe", 145, 50);
		
		g.setColor(Color.BLACK);
		
		int startX = 100;
		int startY = 150;
		int w = 100;
		int wX3 = (w * 3);
		int wX2 = (w * 2);
		
		// initialize cell Rectangles
		int index = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int x = startX + (w * (j % 3));
				int y = startY + (w * (i % 3));
				this.cells[index] = new Rectangle(x, y, w, w);
				index++;
			}
		}
		
		// border
		g.drawLine(startX, startY, startX + wX3, startY);				// top
		g.drawLine(startX, startY, startX, startY + wX3);				// left
		g.drawLine(startX + wX3, startY, startX + wX3, startY + wX3);	// right
		g.drawLine(startX, startY + wX3, startX + wX3, startY + wX3); 	// bottom
		
		// cell bounds
		g.drawLine(startX + w, startY, startX + w, startY + wX3);		// 1st vertical
		g.drawLine(startX + wX2, startY, startX + wX2, startY + wX3);	// 2nd vertical
		g.drawLine(startX, startY + w, startX + wX3, startY + w);		// 1st horizontal
		g.drawLine(startX, startY + wX2, startX + wX3, startY + wX2);	// 2nd horizontal
	}
	
	private void drawX(Graphics g, Rectangle cell) {
		g.setColor(Color.BLUE);
		Graphics2D g2 = (Graphics2D)g;
		g2.setStroke(new BasicStroke(7));
		
		int indent = 25;
		g.drawLine(cell.x + indent, cell.y + indent, cell.x + cell.width - indent, cell.y + cell.height - indent);
		g.drawLine(cell.x + indent, cell.y + cell.height - indent, cell.x + cell.width - indent, cell.y + indent);
	}
	
	private void drawO(Graphics g, Rectangle cell) {
		g.setColor(Color.RED);
		Graphics2D g2 = (Graphics2D)g;
		g2.setStroke(new BasicStroke(7));
		
		int indent = 25;
		g.drawOval(cell.x + indent, cell.y + indent, cell.width - (indent * 2), cell.height - (indent * 2));
	}
	
	// Returns true if this client can play the game (i.e. there are less than 2 clients connected).
	private boolean canPlayGame() {
		if (this.token == null || this.token.equals(""))
			return false;
		return true;
	}
}


	