package repo;
import exception.RepoException;
import model.Animal;

public interface IRepo {
    public void add(Animal a) throws RepoException;
    public void remove(int index) throws IndexOutOfBoundsException;
    public Animal[] getAll();
    public int getLength();
}
