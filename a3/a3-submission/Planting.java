// Name: Rina Osman
// Student id: 300222206

// The Planting Synchronization Problem

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Planting {
    public static void main(String[] args) {
        TA ta = new TA();
        Professor prof = new Professor(ta);
        Student stdnt = new Student(ta);

        stdnt.start();
        prof.start();
        ta.start();

        try {
            prof.join();
        } catch (InterruptedException e) {
        }

        ta.interrupt();
        stdnt.interrupt();
    }
}

// student class
class Student extends Thread {
    TA ta;

    public Student(TA taThread) {
        ta = taThread;
    }

    public void run() {
        while (!isInterrupted()) {
            try {
                ta.studentReady.acquire();
                System.out.println("Student: Got the shovel");
                sleep((int) (100 * Math.random()));
                ta.incrHoleDug();
                System.out.println("Student: Hole " + ta.getHoleDug() + " Dug");
                System.out.println("Student: Letting go of the shovel");
                ta.professorReady.release();

                if (ta.getHoleDug() - ta.getHoleFilled() >= ta.getMAX()) {
                    ta.taReady.release();
                } else {
                    ta.studentReady.release();
                }

            } catch (InterruptedException e) {
                break;
            }
        }
        System.out.println("Student is done");
    }
}

// TA class
class TA extends Thread {

    // Some variables to count number of holes dug and filled - the TA keeps track of things
    private int holeFilledNum;  // number of the hole filled
    private int holePlantedNum;  // number of the hole planted
    private int holeDugNum;     // number of hole dug
    private final int MAX;   // can only get 5 holes ahead
    
    // add semaphores - the professor lets the TA manage things.
    Semaphore studentReady;
    Semaphore professorReady;
    Semaphore taReady;

    public int getMAX() {return MAX;}
    public synchronized void incrHoleDug() {holeDugNum++;}
    public synchronized int getHoleDug() {return holeDugNum;}
    public synchronized void incrHolePlanted() {holePlantedNum++;}
    public synchronized int getHolePlanted() {return holePlantedNum;}
    public synchronized void incrHoleFilled() {holeFilledNum++;}
    public synchronized int getHoleFilled() {return holeFilledNum;}

    public TA() {
        holeFilledNum = 0;
        holePlantedNum = 0;
        holeDugNum = 0;
        MAX = 5;
        studentReady = new Semaphore(1);
        professorReady = new Semaphore(0);
        taReady = new Semaphore(0);
    }

    public void run() {
        while (!isInterrupted()) {
            try {
                taReady.acquire();
                System.out.println("TA: Got the shovel");
                sleep((int) (100 * Math.random()));
                incrHoleFilled();
                System.out.println("TA: The hole " + getHoleFilled() + " has been filled");
                System.out.println("TA: Letting go of the shovel");

                if (getHoleDug() - getHoleFilled() < getMAX()) {
                    studentReady.release();
                } else {
                    taReady.release();
                }

            } catch (InterruptedException e) {
                break;
            }
        }
        System.out.println("TA is done");
    }
}

// professor class
class Professor extends Thread {
    TA ta;

    public Professor(TA taThread) {
        ta = taThread;
    }

    public void run() {
        while (ta.getHolePlanted() <= 20) {
            try {
                ta.professorReady.acquire();
                sleep((int) (50 * Math.random()));
                ta.incrHolePlanted(); // the seed is planted - increment the number	
                System.out.println("Professor: All be advised that I have completed planting hole " + ta.getHolePlanted());
                ta.taReady.release();

            } catch (InterruptedException e) {
                break;
            }
        }
        System.out.println("Professor: We have worked enough for today");
    }

    
}
