package view;

import controller.Controller;
import model.Animal;
import model.Turtle;
import model.Fish;

import exception.RepoException;
import java.util.Scanner;

public class View {
    Controller controller;
    int age = 1;

    public View(Controller controller){
        this.controller = controller;
    }

    public void displayMenu(){
        System.out.println("Choose option: ");
        System.out.println("0. Populate");
        System.out.println("1. Add an entity");
        System.out.println("2. Remove an entity");
        System.out.println("3. Display all");
        System.out.println("4. Filter by age --> age >= 1 year");

        System.out.println("5. Exit");
    }

    public void displayAll(){
        Animal[] animals = controller.getAll();
        for (Animal animal : animals) {
            System.out.println(animal);
        }
    }

    public void display(){
        //print all
        Animal[] filteredAnimals = controller.filterByAge(age);

        for(Animal animal : filteredAnimals){
            System.out.println(animal);
        }
    }

    private void populate() throws RepoException {
        controller.add(new Fish(1, "Trout", "Dark Blue", 1, 1));
        controller.add(new Turtle(400, "Dark Green", 50, 40, "Terrestrial"));
        controller.add(new Fish(500, "Salmon", "Black", 500, 50));
        controller.add(new Turtle(300, "Green", 40, 30, "Marine"));
        controller.add(new Turtle(10, "Light Green", 10, 10, "Marine"));
    }

    private void add() throws RepoException {
        //read from the keyboard
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the type of the animal: ");
        String type = scanner.nextLine();
        System.out.println("Enter the age of the animal: ");
        int age = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Enter the color of the animal: ");
        String color = scanner.nextLine();
        System.out.println("Enter the weight of the animal: ");
        int weight = scanner.nextInt();
        System.out.println("Enter the size of the animal: ");
        int size = scanner.nextInt();

        if (type.equals("Fish")){
            System.out.println("Enter the name of the animal: ");
            scanner.nextLine();
            String name = scanner.nextLine();
            controller.add(new Fish(age, name, color, weight, size));
        }
        else if (type.equals("Turtle")){
            System.out.println("Enter the type (Marine/Terrestrial) of the animal: ");
            scanner.nextLine();
            String medium = scanner.nextLine();
            controller.add(new Turtle(age, color, weight, size, medium));
        }
    }

    private void addElem() throws RepoException{
        controller.add(new Turtle(12, "green", 12, 14, "Aquatic"));
    }

    private void remove() throws IndexOutOfBoundsException{
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of the animal you want to remove: ");
        int index = scanner.nextInt();
        controller.removeByIndex(index);
    }

    public void run() {
        while(true) {
            displayMenu();
            Scanner scanner = new Scanner(System.in);
            int option = scanner.nextInt(); //keyboard input

            switch (option){
                case 0:
                    try {
                        populate();
                        System.out.println("Repo populated successfully");
                    } catch (RepoException e) {
                        e.printStackTrace();
                    }
                    break;
                case 1: //add
                    try {
                        //read from the keyboard
                        add();
                        System.out.println("Animal added successfully");
                    } catch (RepoException e) {
                        e.printStackTrace();
                    }
                    break;
                case 2:
                    try{
                        remove();
                        System.out.println("Item removed successfully");
                    } catch (IndexOutOfBoundsException e) {
                        e.printStackTrace();
                    }
                    break;
                case 3:
                    displayAll();
                    break;
                case 4:
                    display();
                    break;
                case 5:
                    System.exit(0);
            }

        }
    }

}
