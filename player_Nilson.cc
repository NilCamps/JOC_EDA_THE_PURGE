#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Chicoso


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  const vector<Dir> dirs = {Up,Down,Left,Right};
  Pos pos_vacia = Pos({-1, -1});

  Pos buscarRecursos(const Pos& p){
    vector<vector<Pos>> cami(board_rows(), vector<Pos>(board_cols(), pos_vacia));
    queue<Pos> Q;
    Q.push(p);
    cami[p.i][p.j] = p;

    while (not Q.empty()) {
      Pos a = Q.front();
      Q.pop();

      for (Dir d: dirs) {
        Pos s = a+d;
        if (pos_ok(s) and cami[s.i][s.j] == pos_vacia and cell(s).type == Street and cell(s).id == -1) {
          cami[s.i][s.j] = a;
          Q.push(s);
          if (cell(s).bonus == Food or cell(s).bonus == Money) {
            while (cami[s.i][s.j] != p) s = cami[s.i][s.j];
            return s;
          }
        }
      }
    }
    return p;
  }

  Pos buscarEnemy(const Pos& p){
    vector<vector<Pos>> cami(board_rows(), vector<Pos>(board_cols(), pos_vacia));
    queue<Pos> Q;
    Q.push(p);
    cami[p.i][p.j] = p;

    while (not Q.empty()) {
      Pos a = Q.front();
      Q.pop();

      for (Dir d: dirs) {
        Pos s = a+d;
        if (pos_ok(s) and cami[s.i][s.j] == pos_vacia and cell(s).type == Street) {
          cami[s.i][s.j] = a;
          if (cell(s).id == -1) Q.push(s);
          else if (citizen(cell(s).id).player != me()) {
            while (cami[s.i][s.j] != p) s = cami[s.i][s.j];
            return s;
          }
        }
      }
    }
    return p;
  }

  Pos buscarBazooka(const Pos& p){
    vector<vector<Pos>> cami(board_rows(), vector<Pos>(board_cols(), pos_vacia));
    queue<Pos> Q;
    Q.push(p);
    cami[p.i][p.j] = p;

    while (not Q.empty()) {
      Pos a = Q.front();
      Q.pop();

      for (Dir d: dirs) {
        Pos s = a+d;
        if (pos_ok(s) and cami[s.i][s.j] == pos_vacia and cell(s).type == Street and cell(s).id == -1) {
          cami[s.i][s.j] = a;
          Q.push(s);
          if (cell(s).weapon == Bazooka) {
            while (cami[s.i][s.j] != p) s = cami[s.i][s.j];
            return s;
          }
        }
      }
    }
    return p;
  }
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if (is_day()) {
      vector<int> w = warriors(me());
      for (uint i = 0; i < w.size(); ++i){
        int id = w[i];
        Pos p = citizen(id).pos;
        Pos pos_baz = buscarBazooka(citizen(id).pos);
        if(pos_baz != citizen(id).pos){  // si és diferent vol di que hi ha bazooka, per tant es mouria fins la pos_baz
          if(p.i > pos_baz.i){
            move(id,Up);
          }
          if(p.i < pos_baz.i){
             move(id,Down);
          }
          if(p.j > pos_baz.j){
             move(id,Left);
          }
          if(p.j < pos_baz.j){
            move(id,Right);
          }
        }
        else {
          Pos pos_rec = buscarRecursos(citizen(id).pos);
          if(p.i > pos_rec.i){
            move(id,Up);
          }
          if(p.i < pos_rec.i){
             move(id,Down);
          }
          if(p.j > pos_rec.j){
             move(id,Left);
          }
          if(p.j < pos_rec.j){
            move(id,Right);
          }
        }
      }
      vector<int> b = builders(me());
      for (uint i = 0; i < b.size(); ++i){
        int id = b[i];
        Pos p = citizen(id).pos;
        Pos pos_rec = buscarRecursos(citizen(id).pos);
          if(p.i > pos_rec.i){
            move(id,Up);
          }
          if(p.i < pos_rec.i){
             move(id,Down);
          }
          if(p.j > pos_rec.j){
             move(id,Left);
          }
          if(p.j < pos_rec.j){
            move(id,Right);
          }
        }
    }
    if (is_night()){
      vector<int> w = warriors(me());
      for (uint i = 0; i < w.size(); ++i){
        int id = w[i];
        Pos p = citizen(id).pos;
        Pos pos_baz = buscarEnemy(citizen(id).pos);
        if(pos_baz != citizen(id).pos){  // si és diferent vol dir que hi ha bazooka, per tant es mouria fins la pos_baz
          if(p.i > pos_baz.i){
            move(id,Up);
          }
          if(p.i < pos_baz.i){
             move(id,Down);
          }
          if(p.j > pos_baz.j){
             move(id,Left);
          }
          if(p.j < pos_baz.j){
            move(id,Right);
          }
        }
      }
      vector<int> b = builders(me());
      for (uint i = 0; i < b.size(); ++i){
        int id = b[i];
        Pos p = citizen(id).pos;
        Pos pos_rec = buscarRecursos(citizen(id).pos);
          if(p.i > pos_rec.i){
            move(id,Up);
          }
          if(p.i < pos_rec.i){
             move(id,Down);
          }
          if(p.j > pos_rec.j){
             move(id,Left);
          }
          if(p.j < pos_rec.j){
            move(id,Right);
          }
        }
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
