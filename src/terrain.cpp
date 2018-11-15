#include "../include/terrain.hpp"

terrain::terrain(int m, int n, int p, bool fromfile)
{
  if(fromfile)
    custom_generation();
  else{
    m_=m;
    n_=n;
    M_.resize(m_, std::vector<char>(n_));
    random_generation(p);
  }
}

terrain::~terrain(){}

bool terrain::has_end(void){
    if((car_.first==final_.first)&&(car_.second==final_.second))
      return true;
    else
      return false;
}

bool terrain::is_free(int x, int y){
    if(M_[x][y]==' ')
      return true;
    else
      return false;
}

void terrain::random_generation(int p){

  int q;

  for(int i = 0; i < m_; i++){

      for(int j = 0; j < n_; j++){

          std::mt19937_64 rng;
          uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
          std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
          rng.seed(ss);

          q = 10 - p;

          std::default_random_engine generator;
          std::uniform_int_distribution<int> unif(0,q);
          // generates number in the range 0..1
          int dice_roll = unif(rng);

          if(dice_roll == 0)
              M_[i][j] = '0';
          else
              M_[i][j] = ' ';

    }
  }

  int vx, vy;

  while(true){

    std::mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);

    std::uniform_int_distribution<int> unif3(0,m_);
    // generates number in the range 0..1
    vx = unif3(rng);

    std::uniform_int_distribution<int> unif4(0,n_);
    // generates number in the range 0..1
    vy = unif4(rng);


    if(M_[vx][vy]==' '){
      M_[vx][vy] = 'X';
      final_.first = vx;
      final_.second = vy;
      break;
    }
  }


  while(true){

    std::mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);

    std::uniform_int_distribution<int> unif1(0,m_);
    // generates number in the range 0..1
    vx = unif1(rng);

    std::uniform_int_distribution<int> unif2(0,n_);
    // generates number in the range 0..1
    vy = unif2(rng);

    if(M_[vx][vy]==' '){
      M_[vx][vy] = 'Y';
      car_.first = vx;
      car_.second = vy;
      break;
    }
  }
}

void terrain::custom_generation(void){

  // HACER RESIZE DEL VECTOR!!

  std::fstream fs("obstacle.txt", std::ios_base::in);

  int obst_n;
  fs >> obst_n;

  char aux;
  fs >> aux;

  std::vector<int> obst_i;
  std::vector<int> obst_j;

  obst_i.resize(obst_n);
  obst_j.resize(obst_n);


  int i = 0;

  while((i <= obst_n) && (!fs.eof())){

    fs >> obst_i[i] >> aux >> obst_j[i];
    set_pos(obst_i[i], obst_j[i], 'o');

    i++;
  }

  fill();
}

// Para llegar con ' ' las posiciones que no tienen 'o'

void terrain::fill()
{
    //M_.resize()
    for(int i = 0; i < m_; i++){
        for(int j = 0; j < n_; j++){
            if(M_[i][j] != 'o')
                M_[i][j] = ' ';
        }
    }
}

int terrain::get_m(void){
  return m_;
}

int terrain::get_n(void){
  return n_;
}


char terrain::get_pos(int i, int j)
{
    return M_[i][j];
}


void terrain::set_pos(int i, int j, char a)
{
    if((i <= m_) && (j <= n_ ))
        M_[i][j] = a;
}


std::pair<int,int> terrain::get_end(void)
{
    return final_;
}


std::pair<int,int> terrain::get_car(void)
{
    return car_;
}


void terrain::move_car(int x, int y){

  M_[car_.first][car_.second] = '*';
  M_[x][y] = 'Y';
  car_.first = x;
  car_.second = y;
}


void terrain::write_map(void)
{
  std::cout << bold << white;

  for(int i=0; i<m_; i++){

    for(int j=0; j<n_; j++){
      std::cout << on_blue << bold << white;

      if(j == 0)
        std::cout << '|';

      if(M_[i][j] == 'Y'){
        std::cout << on_yellow  << M_[i][j] << ' ' << on_blue;
      }
      else if(M_[i][j] == 'X'){
        std::cout << on_red << M_[i][j] << ' ' << on_blue;
      }
      else if(M_[i][j] == '*'){
        std::cout << bold << on_yellow << M_[i][j] << ' ' << on_blue;
      }
      else{
        std::cout << M_[i][j] << ' ';
      }

      if(j >= (n_ - 1))
        std::cout << '|' << reset << '\n';

    }
  }

  std::cout << "\n\n";
}


void terrain::write_map_grafico(){

  char c;
  initscr();

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_YELLOW);
  attron(COLOR_PAIR(1));

  int y = ((COLS/2) - (m_ + 1));
  int x = ((LINES/2) - ((n_/2) + 1));
      if (x < 0)
        x = 0;
      if (y < 0)
        y = 0;

    //move(0,0);
    //printw(" %d, %d", y, x);
  move (x,y);

    addch(ACS_ULCORNER);
    for(int i = 0; i < m_*2; i++)
      addch (ACS_HLINE);

    addch (ACS_URCORNER);


  for(int i=0; (i<m_) && (i < LINES -1) ; i++){

    move(x+i+1,y);
    addch(ACS_VLINE);

    for(int j=0; (j<n_) && (j < COLS -1); j++){

      if(M_[i][j]=='Y'){
        attron(COLOR_PAIR(2));
        printw("%c ",  M_[i][j]);
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(1));
      }
      else{
        printw("%c ",  M_[i][j]);
      }
    }
      addch(ACS_VLINE);
  }


  move(x + m_ + 1, y);
  addch (ACS_LLCORNER);

  for(int i = 0; i < m_*2; i++)
    addch (ACS_HLINE);

  addch (ACS_LRCORNER);
  attroff(COLOR_PAIR(1));
}
