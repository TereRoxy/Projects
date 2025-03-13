package controller;

import exception.RepoException;
import model.Animal;
import repo.IRepo;
import repo.Repo;

import java.util.Arrays;


public class Controller {
    IRepo repo;
    public Controller(IRepo repo){
        this.repo = repo;
    }

    public Animal[] filterByAge(int age) {
        Animal[] animals = this.repo.getAll();
        Animal[] animalsFiltered = new Animal[Repo.SIZE];
        int currentPos = 0;
        for (int pos = 0; pos < repo.getLength(); pos++){
            if (animals[pos].getAge()/365 >= age){
                animalsFiltered[currentPos++] = animals[pos];
            }
        }
        return Arrays.copyOf(animalsFiltered, currentPos);
//        Animal[] filteredOK = new Animal[currentPos];
//        for(int i=0; i<currentPos; i++){
//            filteredOK[i] = animalsFiltered[i];
//        }
//        return filteredOK;
    }

    public void removeByIndex(int index){
        repo.remove(index);
    }

    public void add(Animal animal) throws RepoException {
        repo.add(animal);
    }

    public Animal[] getAll(){
        Animal[] animals = this.repo.getAll();
        return animals;
    }
}
