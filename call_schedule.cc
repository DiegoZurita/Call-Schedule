#include "ortools/linear_solver/linear_solver.h"
#include "ortools/linear_solver/linear_solver.pb.h"
#include <vector>
#include <string>

using namespace std;

namespace operations_research {

  void Solve(
    MPSolver::OptimizationProblemType optimization_problem_type
  ) {

    MPSolver solver("Glop", optimization_problem_type);

    int agents_number;
    cin>>agents_number;

    int call_per_interval;
    cin>>call_per_interval;

    int intervals_number;
    cin>>intervals_number;

    int customers_number;
    cin>>customers_number;

    int max_call_per_interval = agents_number * call_per_interval;

    cout << "Agents number "<< to_string(agents_number) << endl;
    cout << "Max calls per interval "<< to_string(max_call_per_interval) << endl;
    cout << "Interval number "<< to_string(intervals_number) << endl;
    cout << "Customer number "<< to_string(customers_number) << endl;

    const double infinity = solver.infinity();


    //Creating empty interval constraints
    vector< MPConstraint* > interval_constraints;
    for (int i = 0; i < intervals_number; i++) {
      interval_constraints.push_back(
        solver.MakeRowConstraint(0, max_call_per_interval)
      );
    }

    //Creating empty customer constraints
    vector< MPConstraint* > customer_constraints;
    for (int i = 0; i < customers_number; i++) {
      customer_constraints.push_back(
        solver.MakeRowConstraint(0, 1)
      );
    }

    //Initializing vars 2d vector
    vector< vector< MPVariable* > > vars (
      customers_number, 
      vector< MPVariable* > (intervals_number, NULL)
    );

    //Create objetive function
    MPObjective* const objective = solver.MutableObjective();

    for (int k = 0; k < customers_number; k++) {
      for (int i = 0; i < intervals_number; i++) {

          vars[k][i] = solver.MakeIntVar(0.0, 1, to_string(k) + " - " + to_string(i));

          double temp_val;
          cin>>temp_val;

          objective->SetCoefficient(vars[k][i], temp_val);

          customer_constraints[k]->SetCoefficient(vars[k][i], 1);
          interval_constraints[i]->SetCoefficient(vars[k][i], 1);
      }
    }


    objective->SetMaximization();


    //
    const MPSolver::ResultStatus result_status = solver.Solve();

    if (result_status == MPSolver::OPTIMAL) {
      cout<<endl<<"---- Optimal schedule ----"<<endl;
      cout<<"Customer - Interval"<<endl;

      for (int k = 0; k < customers_number; k++) {

        for (int i = 0; i < intervals_number; i++) { 
          int solution_value = vars[k][i]->solution_value();

          if (solution_value == 1) {
            cout << to_string(k) + "        - " + to_string(i) << "      " << endl;
          }
        }

      }

      cout<< "Optimal objective value = " << objective->Value() << endl;
      cout<< "Problem solved in " << solver.wall_time() << " milliseconds"<<endl;
    }

  }

  void Run() {
    Solve(MPSolver::GLOP_LINEAR_PROGRAMMING);
  }
}

int main(int argc, char** argv) {
  cout<< "---- Integer programming with GLOP ----"<<endl;

  operations_research::Run();
  return 0;
}