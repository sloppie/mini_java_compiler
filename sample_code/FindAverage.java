package com.joocy;

import com.joocy.utilities.MyClass;

public class Legendary {

    public int subjectSize = 5;

    public int findAverage() {
        int mathematics = 78;
        int english = 88;
        int kiswahili = 68;
        int science = 84;
        int ssre = 64;
        int i = 0;

        while(i < subjectSize) {
            int term = mathematics + english + kiswahili + science + ssre;
            term = term / subjectSize;

            i = i + 1;
        }

    }

    public int main() {
        findAverage();
    }

}