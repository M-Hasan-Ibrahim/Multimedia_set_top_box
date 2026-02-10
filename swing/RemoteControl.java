import javax.swing.*;
import java.awt.*;

public class RemoteControl extends JFrame {
    private static final long serialVersionUID = 1L;

    private final JTextArea textArea = new JTextArea(15, 50);
    private int platform = 2; // default, overwritten at startup

    private final Action action1 = new AbstractAction("Button 1") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            textArea.append("Button 1 pressed\n");
        }
    };

    private final Action action2 = new AbstractAction("Button 2") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            textArea.append("Button 2 pressed\n");
        }
    };

    private final Action quitAction = new AbstractAction("Quit") {
        @Override public void actionPerformed(java.awt.event.ActionEvent e) {
            System.exit(0);
        }
    };

    public RemoteControl() {
        super("Step 2 - Menus + Toolbar");

        choosePlatform();

        textArea.setEditable(false);
        add(new JScrollPane(textArea), BorderLayout.CENTER);

        // JPanel buttons = new JPanel();
        // buttons.add(new JButton(action1));
        // buttons.add(new JButton(action2));
        // buttons.add(new JButton(quitAction));
        // add(buttons, BorderLayout.SOUTH);

        setJMenuBar(buildMenuBar());

        add(buildToolBar(), BorderLayout.NORTH);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);

        textArea.append("Platform selected = " + platform + "\n");
    }

    private void choosePlatform() {
        String[] options = { "Windows (1)", "Linux (2)", "WSL (3)" };
        int choice = JOptionPane.showOptionDialog(
                this,
                "Choose your platform:",
                "Platform",
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                options[1]
        );

        if (choice == JOptionPane.CLOSED_OPTION) System.exit(0);

        if (choice == 0) platform = 1;
        else if (choice == 1) platform = 2;
        else platform = 3;
    }

    private JMenuBar buildMenuBar() {
        JMenuBar bar = new JMenuBar();
        JMenu menu = new JMenu("Menu");

        menu.add(new JMenuItem(action1));
        menu.add(new JMenuItem(action2));
        menu.addSeparator();
        menu.add(new JMenuItem(quitAction));

        bar.add(menu);
        return bar;
    }

    private JToolBar buildToolBar() {
        JToolBar tb = new JToolBar();
        tb.add(action1);
        tb.add(action2);
        tb.addSeparator();
        tb.add(quitAction);
        return tb;
    }

    public int getPlatform() { return platform; }

    public static void main(String[] args) {
        System.setProperty("apple.laf.useScreenMenuBar", "true");
        new RemoteControl();
    }
}
