import javax.swing.*;
import java.awt.*;

public class RemoteControl extends JFrame {
    private static final long serialVersionUID = 1L;

    private final JTextArea textArea = new JTextArea(18, 60);

    private final JTextField hostField = new JTextField("127.0.0.1", 12);
    private final JTextField portField = new JTextField("3331", 5);

    private final JTextField nameField  = new JTextField(14);
    private final JTextField groupField = new JTextField(14);

    private Client client = null;
    private int platform = 3;

    private final Action connectAction = new AbstractAction("Connect") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            if (client == null) doConnect();
            else doDisconnect();
        }
    };

    private final Action showAction = new AbstractAction("show") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            String name = nameField.getText().trim();
            if (name.isEmpty()) { append("ERR: enter a name\n"); return; }
            sendAsync("show " + name);
        }
    };

    private final Action showgAction = new AbstractAction("showg") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            String g = groupField.getText().trim();
            if (g.isEmpty()) { append("ERR: enter a group\n"); return; }
            sendAsync("showg " + g);
        }
    };

    private final Action playAction = new AbstractAction("play") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            String name = nameField.getText().trim();
            if (name.isEmpty()) { append("ERR: enter a name\n"); return; }
            sendAsync("play " + name + " " + platform);
        }
    };

    private final Action helpAction = new AbstractAction("help") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            sendAsync("help");
        }
    };

    private final Action availableAction = new AbstractAction("ShowAvailable") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            sendAsync("available");
        }
    };


    private final Action quitAction = new AbstractAction("Quit") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            System.exit(0);
        }
    };

    public RemoteControl() {
        super("Remote Control (Step 3)");

        System.setProperty("apple.laf.useScreenMenuBar", "true");

        choosePlatform();

        textArea.setEditable(false);
        add(new JScrollPane(textArea), BorderLayout.CENTER);

        add(buildToolBar(), BorderLayout.NORTH);
        setJMenuBar(buildMenuBar());

        add(buildSouthPanel(), BorderLayout.SOUTH);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);

        append("Platform selected = " + platform + "\n");
        append("Start C++ server then Connect.\n");
    }

    private JPanel buildSouthPanel() {
        JPanel root = new JPanel();
        root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));

        JPanel conn = new JPanel(new FlowLayout(FlowLayout.LEFT));
        conn.add(new JLabel("Host:"));
        conn.add(hostField);
        conn.add(new JLabel("Port:"));
        conn.add(portField);
        conn.add(new JButton(connectAction));
        root.add(conn);

        JPanel row1 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        row1.add(new JLabel("Name:"));
        row1.add(nameField);
        row1.add(new JButton(showAction));
        row1.add(new JButton(playAction));
        root.add(row1);

        JPanel row2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        row2.add(new JLabel("Group:"));
        row2.add(groupField);
        row2.add(new JButton(showgAction));
        row2.add(new JButton(helpAction));
        row2.add(new JButton(availableAction));
        row2.add(new JButton(quitAction));
        root.add(row2);

        return root;
    }

    private JToolBar buildToolBar() {
        JToolBar tb = new JToolBar();
        tb.add(connectAction);
        tb.addSeparator();
        tb.add(showAction);
        tb.add(showgAction);
        tb.add(playAction);
        tb.addSeparator();
        tb.add(helpAction);
        tb.add(availableAction);
        tb.addSeparator();
        tb.add(quitAction);
        return tb;
    }

    private JMenuBar buildMenuBar() {
        JMenuBar bar = new JMenuBar();

        JMenu server = new JMenu("Server");
        server.add(new JMenuItem(connectAction));
        server.addSeparator();
        server.add(new JMenuItem(helpAction));
        server.add(new JMenuItem(availableAction));
        server.add(new JMenuItem(showAction));
        server.add(new JMenuItem(showgAction));
        server.add(new JMenuItem(playAction));
        bar.add(server);

        JMenu app = new JMenu("App");
        app.add(new JMenuItem(quitAction));
        bar.add(app);

        return bar;
    }

    private void doConnect() {
        final String host = hostField.getText().trim();
        final int port;
        try { port = Integer.parseInt(portField.getText().trim()); }
        catch (Exception ex) { append("ERR: invalid port\n"); return; }

        append("Connecting to " + host + ":" + port + " ...\n");

        new SwingWorker<Void, Void>() {
            @Override protected Void doInBackground() throws Exception {
                client = new Client(host, port);
                return null;
            }
            @Override protected void done() {
                try {
                    get();
                    append("Connected.\n");
                    connectAction.putValue(Action.NAME, "Disconnect");
                } catch (Exception ex) {
                    append("ERR: " + ex.getMessage() + "\n");
                    client = null;
                }
            }
        }.execute();
    }

    private void doDisconnect() {
        append("Disconnecting...\n");
        client = null;
        connectAction.putValue(Action.NAME, "Connect");
        append("Disconnected.\n");
    }

    private void sendAsync(final String cmd) {
        if (client == null) { append("ERR: not connected\n"); return; }

        append("> " + cmd + "\n");

        new SwingWorker<String, Void>() {
            @Override protected String doInBackground() {
                String resp = client.send(cmd); 
                return resp;
            }
            @Override protected void done() {
                try {
                    String resp = get();
                    if (resp == null) {
                        append("ERR: no response\n");
                        return;
                    }
                    append(resp.replace(';', '\n') + "\n");
                } catch (Exception ex) {
                    append("ERR: " + ex.getMessage() + "\n");
                }
            }
        }.execute();
    }

    private void append(String s) {
        textArea.append(s);
        textArea.setCaretPosition(textArea.getDocument().getLength());
    }

    private void choosePlatform() {
        String[] options = { "Windows (1)", "Linux (2)", "WSL (3)" };
        int choice = JOptionPane.showOptionDialog(
                this, "Choose your platform:", "Platform",
                JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE,
                null, options, options[1]
        );
        if (choice == JOptionPane.CLOSED_OPTION) System.exit(0);
        platform = (choice == 0) ? 1 : (choice == 1) ? 2 : 3;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(RemoteControl::new);
    }
}
