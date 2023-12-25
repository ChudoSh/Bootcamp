package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

import java.util.List;
import java.util.ArrayList;

public class CallCenter {
    private List<Manager> managers;

    public void handleCall(Call call) {
    }

    private class Respondent extends CallCenterEmployee {
        private Supervisor supervisor;

        public Respondent(Supervisor supervisor) {
            this.supervisor = supervisor;
        }

        @Override
        public Call handle(Call call) {
            return null;
        }
    }

    private class Supervisor extends CallCenterEmployee {
        private List<Respondent> respondents;
        private Manager manager;

        public Supervisor(Manager manager) {
            this.manager = manager;
            this.respondents = new ArrayList<>();
        }

        @Override
        public Call handle(Call call) {
            return null;
        }
    }

    private class Manager extends CallCenterEmployee {
        private List<Supervisor> supervisors;

        public Manager() {
            this.supervisors = new ArrayList<>();
        }

        @Override
        public Call handle(Call call) {
            return null;
        }
    }

    private class Director extends CallCenterEmployee {
        public Call handle(Call call) {
            return null;
        }
    }
}

abstract class CallCenterEmployee {
    private boolean isAvailable = true;

    public abstract Call handle(Call call);

    public void setAvailable() {
        this.isAvailable = true;
    }

    public void setBusy() {
        this.isAvailable = false;
    }

    public boolean isAvailable() {
        return this.isAvailable;
    }
}

interface Call {
    String call();

    boolean isHandled();
}

