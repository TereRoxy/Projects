package repo;

import exception.RepoException;
import model.Animal;

public class Repo implements IRepo{
    private final Animal[] animals;
    private int length;
    public static int SIZE = 10;

    public Repo() {
        this.animals = new Animal[SIZE];
        this.length = 0;
    }

    @Override
    public void add(Animal a) throws RepoException {
        if (this.length >= SIZE)
            throw new RepoException("Item is out of bounds");
        this.animals[this.length++] = a;
    }

    @Override
    public void remove(int index) throws IndexOutOfBoundsException{
        if (index >= 0 && index < getLength()){
            for (int i=index; i<getLength()-1; i++)
            {
                this.animals[i] = this.animals[i+1];
            }
            this.animals[getLength()-1] = null;
            length--;
        }
        else{
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
    }

    @Override
    public Animal[] getAll(){
        Animal[] allAnimals = new Animal[getLength()];
        for (int i=0; i<getLength(); i++) {
            allAnimals[i] = animals[i];
        }
        return allAnimals;
    }

    @Override
    public int getLength() {
        return this.length;
    }
}
