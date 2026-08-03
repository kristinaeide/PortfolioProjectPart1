public class SequentialCounterApp {

    static class CountUpThread extends Thread {

        @Override
        public void run() {
            System.out.println("Thread One: Counting Up");

            for (int i = 0; i <= 20; i++) {
                System.out.println(i);

                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    System.out.println("Count up thread was interrupted.");
                }
            }
        }
    }

    static class CountDownThread extends Thread {

        @Override
        public void run() {
            System.out.println("\nThread Two: Counting Down");

            for (int i = 20; i >= 0; i--) {
                System.out.println(i);

                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    System.out.println("Count down thread was interrupted.");
                }
            }
        }
    }

    public static void main(String[] args) {

        CountUpThread threadOne = new CountUpThread();
        CountDownThread threadTwo = new CountDownThread();

        try {
            threadOne.start();

            // Wait until the first thread finishes
            threadOne.join();

            // Start the second thread
            threadTwo.start();

            // Wait until the second thread finishes
            threadTwo.join();

        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("\nProgram Complete!");
    }
}