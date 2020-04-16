package com.joocy;

import com.joocy.utilities.MyClass;
import java.util.FileWriter;
import java.util.FileReader;

public class Legendary {

    public int subjectSize = 5;
    public String myString = "Legends they never die";
    public boolean myBoolean = false;

    public int findAverage() {
        int mathematics = 78;
        int english = 88;
        int kiswahili = 68;
        int science = 84;
        int ssre = 64;
        int i = 0;
        boolean secondBool = (kiswahili >= english && science < ssre || mathematics < science);
        String mySecondString = "Legends";

        while(i < subjectSize) {
            int term = mathematics + english + kiswahili + science + ssre;
            term = term / subjectSize;

            i = i + 1;
        }

    }

    public int main() {
        findAverage();

        int new = 0;
        int next;

        if(new == next) {
            next = new + 1;
        } else if(new >= next) {
            double v = 76.8 + 90.21;
        } else {
            float variable = 34.567;
        }

        String complete = "Average computing done";
        System.out.println(complete);

    }

}