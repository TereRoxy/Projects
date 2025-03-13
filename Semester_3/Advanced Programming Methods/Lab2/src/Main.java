//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
import controller.Controller;
import repo.Repo;
import view.View;

import exception.RepoException;

public class Main {
    public static void main(String[] args) {
        //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.
        Repo repo = new Repo();
        Controller controller = new Controller(repo);
        View view = new View(controller);

        view.run();
    }

    //8. Intr-un acvariu traiesc pesti si broaste testoase.
    //Sa se afiseze toate vietuitoarele din acvariu care sunt
    //mai batrine de 1 an.
}