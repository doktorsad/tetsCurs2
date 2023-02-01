#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

class MagicCarpet;
class Eagle;
class Broomstick;
class Camel;
class CamelIsFast;
class Centaur;
class AllTerrainBoots;
class RaceInAir;
class RaceOnGround;
class RaceOnGrondAndInAir;

enum class TRANSPORT_AIR{
    BROOMSTICK,
    MAGIC_CARPET,
    EAGLE,
    MAX_NUMB
};

enum class TRANSPORT_GROUND{
    CAMEL_IS_FAST,
    CENTAUR,
    CAMEL,
    ALL_TERRAIN_BOOTS,
    MAX_NUMB
};

enum class TRANSPORT_ALL{
    CAMEL_IS_FAST,
    CENTAUR,
    CAMEL,
    ALL_TERRAIN_BOOTS,
    BROOMSTICK,
    MAGIC_CARPET,
    EAGLE,
    MAX_NUMB
};

class TransportVehicle {
public:
    virtual std::string get_name() const = 0;
protected:
    int speed;
    std::string name;
    std::string specialization;
    virtual ~TransportVehicle() = default;
    TransportVehicle& operator=(const TransportVehicle&) = delete;
    TransportVehicle() = default;
};

class ITransportGround : public TransportVehicle {
protected:
    virtual ~ITransportGround() = default;
    ITransportGround& operator=(const ITransportGround&) = delete;
    ITransportGround() = default;
public:
    virtual std::string get_name() const = 0;
    virtual std::string get_specialization() const = 0;
    virtual int get_speed() const = 0;
    virtual int get_time_before_bedtime() const = 0;
    virtual double get_this_sleep_time() const = 0;
    virtual double get_update_sleep() const = 0;
    virtual double get_update_sleep_second() const = 0;

    static std::shared_ptr<Camel> creat_camel() {
        return std::make_shared<Camel>();
    }
    static std::shared_ptr<CamelIsFast> creat_camel_is_fast() {
        return std::make_shared<CamelIsFast>();
    }
    static std::shared_ptr<Centaur> creat_centaur() {
        return std::make_shared<Centaur>();
    }
    static std::shared_ptr<AllTerrainBoots> creat_all_terrain_boots() {
        return std::make_shared<AllTerrainBoots>();
    }
};

class ITransportAir : public TransportVehicle {
protected:
    virtual ~ITransportAir() = default;
    ITransportAir& operator=(const ITransportAir&) = delete;
    ITransportAir() = default;
public:
    virtual std::string get_name() const = 0;
    virtual std::string get_specialization() const = 0;
    virtual int get_speed() const = 0;
    virtual double get_shortening_the_distatnce() const = 0;

    static std::shared_ptr<MagicCarpet> creat_magic_carpet(const int& distance) {
        return std::make_shared<MagicCarpet>(distance);
    }
    static std::shared_ptr<Eagle> creat_eagle() {
        return std::make_shared<Eagle>();
    }
    static std::shared_ptr<Broomstick> creat_broomstick(const int& distance) {
        return std::make_shared<Broomstick>(distance);
    }
};

class TransportVehicleInAir : public ITransportAir {
protected:
    virtual ~TransportVehicleInAir() = default;
    double shortening_the_distance;
    TransportVehicleInAir() = default;
    std::string get_name() const override { return this->name; }
    std::string get_specialization()  const override { return this->specialization; }
    int get_speed() const override { return this->speed; }
};

class MagicCarpet : public TransportVehicleInAir {
public:
    MagicCarpet(const int& distance) {
        this->speed = 10;
        this->name = "Magic Carpet";
        this->specialization = "air";
        if (distance < 1000)
            this->shortening_the_distance = 1;
        else if (distance < 5000 && distance >= 1000)
            this->shortening_the_distance = 0.97;
        else if (distance < 10000 && distance >= 5000)
            this->shortening_the_distance = 0.9;
        else if (distance >= 10000)
            this->shortening_the_distance = 0.95;
    }
    double get_shortening_the_distatnce() const override { return this->shortening_the_distance; }
};

class Eagle : public TransportVehicleInAir {
public:
    Eagle() {
        this->speed = 8;
        this->name = "Eagle";
        this->shortening_the_distance = 0.92;
        this->specialization = "air";
    }
    double get_shortening_the_distatnce() const override { return this->shortening_the_distance; }
};

class Broomstick : public TransportVehicleInAir {
public:
    Broomstick() = delete;
    Broomstick(const int& distance) {
        this->speed = 20;
        this->name = "Broomstick";
        this->shortening_the_distance = 1 - ((distance / static_cast<double>(1000)) / 100);
        this->specialization = "air";
    }
    double get_shortening_the_distatnce() const override { return this->shortening_the_distance; }
};

class TransportVehicleGround : public ITransportGround {
protected:
    virtual ~TransportVehicleGround() = default;
    int time_befor_bedtime;
    double sleep_time;
    TransportVehicleGround() = default;
    int get_time_before_bedtime() const override { return this->time_befor_bedtime; }
    double get_this_sleep_time() const override { return this->sleep_time; }
    std::string get_name() const override { return this->name; }
    std::string get_specialization() const override { return this->specialization; }
    int get_speed() const override { return speed; }
    double get_update_sleep() const override { return 0; }
    double get_update_sleep_second() const override { return 0; }
};

class Camel : public TransportVehicleGround {
public:
    Camel() {
        this->speed = 10;
        this->time_befor_bedtime = 30;
        this->sleep_time = 5;
        this->specialization = "ground";
        this->name = "Camel";
    }
    double get_update_sleep() const override final { return 6; }
};

class CamelIsFast : public TransportVehicleGround {
public:
    CamelIsFast() {
        this->speed = 40;
        this->time_befor_bedtime = 10;
        this->sleep_time = 5;
        this->name = "Camel Fast";
        this->specialization = "ground";
    }
    double get_update_sleep() const override final { return 6.5; }
    double get_update_sleep_second() const override final { return 8; }
};

class Centaur : public TransportVehicleGround {
public:
    Centaur() {
        this->speed = 15;
        this->time_befor_bedtime = 8;
        this->sleep_time = 2;
        this->name = "Centaur";
        this->specialization = "ground";
    }
};

class AllTerrainBoots : public TransportVehicleGround {
public:
    AllTerrainBoots() {
        this->speed = 6;
        this->time_befor_bedtime = 60;
        this->sleep_time = 10;
        this->name = "All Terrain Boots";
        this->specialization = "ground";
    }
    double get_update_sleep() const override final { return 5; }
};

class Race {
protected:
    int distance;
    Race() = default;
    virtual ~Race() = default;
};

class IRaceAir : public Race {
protected:
    virtual ~IRaceAir() = default;
    IRaceAir& operator= (const IRaceAir&) = delete;
    IRaceAir() = default;
public:
    virtual void bubble_sort_transport() = 0;
    virtual std::string get_name(const int& i) const = 0;
    virtual void set_magic_carpet() = 0;
    virtual void set_eagle() = 0;
    virtual void set_broomstick() = 0;
    virtual int get_size() const = 0;
    virtual double get_time(const int& i) const = 0;
    static std::shared_ptr<RaceInAir> creat_race_in_air(const int& distance) {
        return std::make_shared<RaceInAir>(distance);
    }
};

class IRaceGround : public Race {
protected:
    virtual ~IRaceGround() = default;
    IRaceGround& operator= (const IRaceGround&) = delete;
    IRaceGround() = default;
public:
    virtual void bubble_sort_transport() = 0;
    virtual std::string get_name(const int& i) const = 0;
    virtual void set_camel() = 0;
    virtual void set_camel_is_fast() = 0;
    virtual void set_centaur() = 0;
    virtual void set_all_terrain_boots() = 0;
    virtual int get_size() const = 0;
    virtual double get_time (const int& i) const = 0;
    static std::shared_ptr<RaceOnGround> creat_race_on_ground(const int& distance) {
        return std::make_shared<RaceOnGround>(distance);
    }
};

class IRaceAirGround : public Race {
protected:
    virtual ~IRaceAirGround() = default;
    IRaceAirGround& operator= (const IRaceAirGround&) = delete;
    IRaceAirGround() = default;
public:
    virtual void bubble_sort_transport() = 0;
    virtual std::string get_name_air_vec(const int& i) const = 0;
    virtual std::string get_name_ground_vec(const int& i) const = 0;
    virtual std::string get_name_air_ground_vec(const int& i) const = 0;
    virtual std::string get_specilization_air_vec(const int& i) const = 0;
    virtual std::string get_specilization_ground_vec(const int& i) const = 0;
    virtual void set_magic_carpet() = 0;
    virtual void set_eagle() = 0;
    virtual void set_broomstick() = 0;
    virtual void set_camel() = 0;
    virtual void set_camel_is_fast() = 0;
    virtual void set_centaur() = 0;
    virtual void set_all_terrain_boots() = 0;
    virtual int get_size_air_vec() const = 0;
    virtual int get_size_ground_vec() const = 0;
    virtual int get_size_air_ground_vec() const = 0;
    virtual double get_time (const int& i) const  = 0;
    static std::shared_ptr<RaceOnGrondAndInAir> creat_race_on_ground_in_air(const int& distance) {
        return std::make_shared<RaceOnGrondAndInAir>(distance);
    }
};

class RaceInAir : public IRaceAir {
protected:
    std::vector <std::shared_ptr<ITransportAir > > transports;
public:
    RaceInAir() = delete;
    RaceInAir(const int& distance) { this->distance = distance;}
    void bubble_sort_transport() override {
        std::sort(this->transports.begin(), transports.end(), [](const auto& rhs, const auto& lhs) {
            return rhs->get_shortening_the_distatnce() / rhs->get_speed() <
                lhs->get_shortening_the_distatnce() / lhs->get_speed();
            });
    }
    std::string get_name(const int& i) const override final { return transports[i]->get_name(); }
    int get_size() const override {return transports.size();}
    void set_magic_carpet() override final {
        transports.push_back(ITransportAir::creat_magic_carpet(this->distance));
    }
    void set_eagle() override final{
        transports.push_back(ITransportAir::creat_eagle());
    }
    void set_broomstick() override final{
        transports.push_back(ITransportAir::creat_broomstick(this->distance));
    }
    double get_time(const int& i) const override final {
        return ((distance * transports[i]->get_shortening_the_distatnce()) / transports[i]->get_speed());
    }
};

class RaceOnGround : public IRaceGround {
protected:
    std::vector <std::shared_ptr<ITransportGround > > transports;
public:
    RaceOnGround() = delete;
    RaceOnGround(const int& distance) { this->distance = distance; }
    void bubble_sort_transport() override {
        for (size_t idx_i = 0; idx_i + 1 < transports.size(); ++idx_i) {
            for (size_t idx_j = 0; idx_j + 1 < transports.size() - idx_i; ++idx_j) {
                if (get_time(idx_j + 1) < get_time(idx_j)) {
                    std::swap(transports[idx_j], transports[idx_j + 1]);
                }
            }
        }
    }
    std::string get_name(const int& i) const override final { return transports[i]->get_name(); }
    int get_size() const override final {return transports.size();}
    void set_camel() override final {
        transports.push_back(ITransportGround::creat_camel());
    }
    void set_camel_is_fast() override final {
        transports.push_back(ITransportGround::creat_camel_is_fast());
    }
    void set_centaur() override final {
        transports.push_back(ITransportGround::creat_centaur());
    }
    void set_all_terrain_boots() override final {
        transports.push_back(ITransportGround::creat_all_terrain_boots());
    }
    double get_time (const int& i) const override final {
        double time = static_cast<double>(this->distance) / static_cast<double>(transports[i]->get_speed());
        int cycle = static_cast<int>(time) / transports[i]->get_time_before_bedtime();
        if (transports[i]->get_name() == "Camel" || transports[i]->get_name() == "All Terrain Boots") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    if (k == 1) {
                        time += transports[i]->get_this_sleep_time();
                        continue;
                    }
                    time += transports[i]->get_update_sleep();
                }
            }
            return time;
        }
        else if (transports[i]->get_name() == "Camel Fast") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    if (k == 0) {
                        time += transports[i]->get_this_sleep_time();
                        continue;
                    }
                    if (k == 1) {
                        time += transports[i]->get_update_sleep();
                        continue;
                    }
                    time += transports[i]->get_update_sleep_second();
                }
            }
            return time;
        }
        else if (transports[i]->get_name() == "Centaur") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    time += transports[i]->get_this_sleep_time();
                }
            }
            return time;
        }
        return 0;
    }

};

class RaceOnGrondAndInAir : public IRaceAirGround {
protected:
    std::vector <std::shared_ptr<ITransportAir > > transports_first;
    std::vector <std::shared_ptr<ITransportGround > > transports_second;
    std::vector <std::shared_ptr<TransportVehicle > > transport_all;
    std::vector <double> time;
public:
    RaceOnGrondAndInAir() = delete;
    RaceOnGrondAndInAir(const int& distance) {
        this->distance = distance; 
    }

    void bubble_sort_transport() override final {
        sort_transport_air();
        sort_transport_ground();
        int idx_i = 0;
        int idx_k = 0;
        while (true) {
            if (get_time_air(idx_i) > get_time_ground(idx_k)) {
                transport_all.push_back(transports_second[idx_k]);
                time.push_back(get_time_ground(idx_k));
                ++idx_k;
            }else if (get_time_air(idx_i) < get_time_ground(idx_k)) {
                transport_all.push_back(transports_first[idx_i]);
                time.push_back(get_time_air(idx_i));
                ++idx_i;
            } else if(get_time_air(idx_i) == get_time_ground(idx_k)){
                transport_all.push_back(transports_first[idx_i]);
                transport_all.push_back(transports_second[idx_k]);
                time.push_back(get_time_air(idx_i));
                time.push_back(get_time_ground(idx_k));
                ++idx_k;
                ++idx_i;
            }
            if (idx_i == transports_first.size()) {
                for (int i = idx_k; i < transports_second.size(); ++i) {
                    transport_all.push_back(transports_second[i]);
                    time.push_back(get_time_ground(i));
                }
                break;
            }
            if (idx_k == transports_second.size()) {
                for (int i = idx_i; i < transports_first.size(); ++i) {
                    transport_all.push_back(transports_first[i]);
                    time.push_back(get_time_air(i));
                }
                break;
            }
        }
    }
    void set_magic_carpet() override final {
        transports_first.push_back(ITransportAir::creat_magic_carpet(this->distance));
    }
    void set_eagle() override final {
        transports_first.push_back(ITransportAir::creat_eagle());
    }
    void set_broomstick() override final {
        transports_first.push_back(ITransportAir::creat_broomstick(this->distance));
    }
    void set_camel() override final {
        transports_second.push_back(ITransportGround::creat_camel());
    }
    void set_camel_is_fast() override final {
        transports_second.push_back(ITransportGround::creat_camel_is_fast());
    }
    void set_centaur() override final {
        transports_second.push_back(ITransportGround::creat_centaur());
    }
    void set_all_terrain_boots() override final {
        transports_second.push_back(ITransportGround::creat_all_terrain_boots());
    }
    std::string get_name_air_vec(const int& i) const override final{
        return transports_first[i]->get_name();
    }
    std::string get_name_ground_vec(const int& i) const override final{
        return transports_second[i]->get_name();
    }
    std::string get_name_air_ground_vec(const int& i) const override final{
        return transport_all[i]->get_name();
    }
    std::string get_specilization_air_vec(const int &i) const override final{
        return transports_first[i]->get_specialization();
    }
    std::string get_specilization_ground_vec(const int& i) const override final{
        return transports_second[i]->get_specialization();
    }
    int get_size_air_vec() const override final{return transports_first.size();}
    int get_size_ground_vec() const override final{return transports_second.size();}
    int get_size_air_ground_vec() const override final{return transport_all.size();}
    double get_time(const int &i)const override final{return this->time[i];}
protected:
    void sort_transport_air() {
        for (size_t idx_i = 0; idx_i + 1 < transports_first.size(); ++idx_i) {
            for (size_t idx_j = 0; idx_j + 1 < transports_first.size() - idx_i; ++idx_j) {
                if (get_time_air(idx_j + 1) < get_time_air(idx_j)) {
                    std::swap(transports_first[idx_j], transports_first[idx_j + 1]);
                }
            }
        }
    }

    void sort_transport_ground() {
        for (size_t idx_i = 0; idx_i + 1 < transports_second.size(); ++idx_i) {
            for (size_t idx_j = 0; idx_j + 1 < transports_second.size() - idx_i; ++idx_j) {
                if (get_time_ground(idx_j + 1) < get_time_ground(idx_j)) {
                    std::swap(transports_second[idx_j], transports_second[idx_j + 1]);
                }
            }
        }
    }

    double get_time_ground(const int& i) {
        double time = static_cast<double>(this->distance) / static_cast<double>(transports_second[i]->get_speed());
        int cycle = static_cast<int>(time) / transports_second[i]->get_time_before_bedtime();
        if (transports_second[i]->get_name() == "Camel" || transports_second[i]->get_name() == "All Terrain Boots") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    if (k == 1) {
                        time += transports_second[i]->get_this_sleep_time();
                        continue;
                    }
                    time += transports_second[i]->get_update_sleep();
                }
            }
            return time;
        }
        else if (transports_second[i]->get_name() == "Camel Fast") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    if (k == 0) {
                        time += transports_second[i]->get_this_sleep_time();
                        continue;
                    }
                    if (k == 1) {
                        time += transports_second[i]->get_update_sleep();
                        continue;
                    }
                    time += transports_second[i]->get_update_sleep_second();
                }
            }
            return time;
        }
        else if (transports_second[i]->get_name() == "Centaur") {
            if (cycle >= 1) {
                for (int k = 0; k < cycle; ++k) {
                    time += transports_second[i]->get_this_sleep_time();
                }
            }
            return time;
        }
        return 0;
    }

    double get_time_air(const int& i) {
        return ((distance * transports_first[i]->get_shortening_the_distatnce()) / transports_first[i]->get_speed());
    }
};

int greeting_out_and_choice(){
    std::cout << "Welcome to this wonderful game.\n"
        << "Choose a track where the best racers and their vehicles will fight.\n"
        << "air route [1]\nland route [2]\nland-air route [3]\n"
        << "To exit, press [0] \n";
    int choice = 0;
    while(true){
        std::cout << "Your choice => ";
        std::cin >> choice;
        if(std::cin.fail() || choice > 3 || choice < 0){
            std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    std::cout << "Erroneous input, try again" << '\n';
	    }
	    else{
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;            
        }
    }
    if(choice == 0){
        std::cout << "Good bye\n";
        exit(0);
    }
    return choice;
}

int distance_sampling(){
    int distance = 0;
    std::cout << "Congratulations, you have chosen the track.\nNow select the route distance.\n";
    while(true){
        std::cout << "Your choice => ";
        std::cin >> distance;
        if(std::cin.fail() || distance <= 0){
            std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    std::cout << "Erroneous input, try again" << '\n';
	    }
	    else{
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;            
        }  
    } 
    return distance;
}

template <typename PTR_RACE>
void table_name_time_output_only_race_air_and_only_race_ground(const std::shared_ptr<PTR_RACE> race){
    std::cout << std::setw(25) <<"Table of participants" << '\n';
    std::cout << std::setw(20) << "*Participants*" << std::setw(12) << "*Time*\n";
    for(int idx_i = 0; idx_i < race->get_size(); ++idx_i){
        std::cout << "|" << std::setw(20) << race->get_name(idx_i) << "|";
        std::cout << std::setw(10) << race->get_time(idx_i) << "|" << '\n';
    }
}

template <typename PTR_RACE>
void table_name_output_only_race_air_and_only_race_ground(const std::shared_ptr<PTR_RACE> race){
    std::cout << std::setw(25) <<"Table of participants" << '\n';
    std::cout << std::setw(20) << "*Participants*\n";
    for(int idx_i = 0; idx_i < race->get_size(); ++idx_i){
        std::cout << "|" <<std::setw(20) << race->get_name(idx_i) << "|" <<'\n';
    }
}

void table_name_output_all_race(const std::shared_ptr<IRaceAirGround> race){
    std::cout << std::setw(30) <<"Table of participants" << '\n';
    std::cout << std::setw(25) << "*Participants*\n";
    for(int idx_i = 0; idx_i < race->get_size_air_vec(); ++idx_i){
        std::cout << "|" << std::setw(20) << race->get_name_air_vec(idx_i);
        std::cout << std::setw(10) << race->get_specilization_air_vec(idx_i) << "|" <<'\n';
    }
    for(int idx_i = 0; idx_i < race->get_size_ground_vec(); ++idx_i){
        std::cout << "|" << std::setw(20) << race->get_name_ground_vec(idx_i);
        std::cout << std::setw(10) << race->get_specilization_ground_vec(idx_i) << "|" <<'\n';
    }    
}

void table_name_time_output_all_race(const std::shared_ptr<IRaceAirGround> race){
    std::cout << std::setw(30) <<"Table of participants" << '\n';
    std::cout << std::setw(20) << "*Participants*" << std::setw(20) << "*Time*\n";
    for(int idx_i = 0; idx_i < race->get_size_air_ground_vec(); ++idx_i){
        std::cout << "|" << std::setw(20) << race->get_name_air_ground_vec(idx_i) << "|";
        std::cout << std::setw(20) << race->get_time(idx_i) << "|" << '\n';
    }
}

bool exit_register(const int &minimum_number_vehicles){
    if(minimum_number_vehicles < 2){
        std::cout << "The minimum number of vehicles must be more than two.\n";
        return true;
    }
    int choice_again = 1;
    std::cout << "Don't you want to choose again? Yes [1] or No [0]\n";
    while(true){
        std::cout << "Your choice => ";
        std::cin >> choice_again;
        if(std::cin.fail() || choice_again > 1 || choice_again < 0){
            std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    std::cout << "Erroneous input, try again" << '\n';
	    }
	    else{
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;  
        }       
    }
    if(choice_again == 1)
        return true;
    return false;
}

void cheking_vehicle_selection(int& choice, const int & max_numb_vehicle){
    while(true){
            std::cout << "Your choice of vehicle => ";
            std::cin >> choice;
            if(std::cin.fail() || choice > max_numb_vehicle || choice < 0){
                std::cin.clear();
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		        std::cout << "Erroneous input, try again" << '\n';
	        }
	        else{
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;  
            }         
        }
}

bool checking_vectors_emptiness(const std::shared_ptr<IRaceAirGround> &race){
    if(race->get_size_air_vec() == 0){
            std::cout << "You need to enter at least one air transport\n";
            return true;
    }
    if(race->get_size_ground_vec() == 0){
            std::cout << "You need to enter at least one ground transport\n";
            return true;
        }
    return false;
}

void game_race_air(const int &distance){
    int choice = 0;
    int minimum_number_vehicles = 0;
    int counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::MAX_NUMB)]{0,0,0};
    std::shared_ptr<IRaceAir> race = IRaceAir::creat_race_in_air(distance);
    std::cout << "Register transports to participate in the race.\n"
        << "Broomstick [1]\nMagic Carpet [2]\nEagle [3]\n" 
        << "To exit, press [0]\n";
    while(true){
        cheking_vehicle_selection(choice, static_cast<int>(TRANSPORT_AIR::MAX_NUMB));
        switch(choice){
            case 1: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::BROOMSTICK)] == 0){
                        race->set_broomstick();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::BROOMSTICK)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                    break;
                    }
            case 2: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::MAGIC_CARPET)] == 0){
                        race->set_magic_carpet();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::MAGIC_CARPET)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                    break;
                    }
            case 3: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::EAGLE)] == 0){
                        race->set_eagle();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_AIR::EAGLE)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
        }
        if(minimum_number_vehicles == static_cast<int>(TRANSPORT_AIR::MAX_NUMB))
            break;      
        if(choice == 0){
            if(exit_register(minimum_number_vehicles))
                continue;
            else
                break;
        }
    }
    table_name_output_only_race_air_and_only_race_ground(race);
    std::cout << "The race has begun\nNow we will find out the winners\n";
    race->bubble_sort_transport();
    table_name_time_output_only_race_air_and_only_race_ground(race);
}

void game_race_ground(const int &distance){
    int choice = 0;
    int minimum_number_vehicles = 0;
    int counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::MAX_NUMB)]{0,0,0};
    std::shared_ptr<IRaceGround> race = IRaceGround::creat_race_on_ground(distance);
    std::cout << "Register transports to participate in the race.\n"
        << "Camel is fast [1]\nCentraur [2]\nCamel [3]\nAll Terrain Boots [4]\n"
        << "To exit, press [0]\n";
    while(true){
        cheking_vehicle_selection(choice, static_cast<int>(TRANSPORT_GROUND::MAX_NUMB));
        switch(choice){
            case 1: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CAMEL_IS_FAST)] == 0){
                        race->set_camel_is_fast();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CAMEL_IS_FAST)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 2: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CENTAUR)] == 0){
                        race->set_centaur();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CENTAUR)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 3: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CAMEL)] == 0){
                        race->set_camel();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::CAMEL)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 4: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::ALL_TERRAIN_BOOTS)] == 0){
                        race->set_all_terrain_boots();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_GROUND::ALL_TERRAIN_BOOTS)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
                
        }
        if(minimum_number_vehicles == static_cast<int>(TRANSPORT_GROUND::MAX_NUMB))
            break;      
        if(choice == 0){
            if(exit_register(minimum_number_vehicles))
                continue;
            else
                break;
        }
    }
    table_name_output_only_race_air_and_only_race_ground(race);
    std::cout << "The race has begun\nNow we will find out the winners\n";
    race->bubble_sort_transport();
    table_name_time_output_only_race_air_and_only_race_ground(race);
}

void game_race_air_and_ground(const int &distance){
    int choice = 0;
    int minimum_number_vehicles = 0;
    int counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::MAX_NUMB)]{0,0,0};
    std::shared_ptr<IRaceAirGround> race = IRaceAirGround::creat_race_on_ground_in_air(distance);
    std::cout << "Register transports to participate in the race.\n"
        << "Camel is fast [1]\nCentraur [2]\nCamel [3]\nAll Terrain Boots [4]\n" 
        << "Broomstick [5]\nMagic Carpet [6]\nEagle [7]\n"
        << "To exit, press [0]\n";
    while(true){
        cheking_vehicle_selection(choice, static_cast<int>(TRANSPORT_ALL::MAX_NUMB));
        switch(choice){
            case 1: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CAMEL_IS_FAST)] == 0){
                        race->set_camel_is_fast();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CAMEL_IS_FAST)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 2: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CENTAUR)] == 0){
                        race->set_centaur();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CENTAUR)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 3: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CAMEL)] == 0){
                        race->set_camel();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::CAMEL)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 4: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::ALL_TERRAIN_BOOTS)] == 0){
                        race->set_all_terrain_boots();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::ALL_TERRAIN_BOOTS)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
            case 5: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::BROOMSTICK)] == 0){
                        race->set_broomstick();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::BROOMSTICK)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                    break;
                    }
            case 6: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::MAGIC_CARPET)] == 0){
                        race->set_magic_carpet();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::MAGIC_CARPET)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                    break;
                    }
            case 7: if(counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::EAGLE)] == 0){
                        race->set_eagle();
                        ++minimum_number_vehicles;
                        ++counter_selected_vehicle[static_cast<int>(TRANSPORT_ALL::EAGLE)];
                        break;
                    }else{
                        std::cout << "You have already registered this vehicle\n";
                        break;
                    }
        }
        if(minimum_number_vehicles == static_cast<int>(TRANSPORT_ALL::MAX_NUMB))
            break;
        if(choice == 0){
            if(exit_register(minimum_number_vehicles)){
                continue;
            }
            else{
                if(!checking_vectors_emptiness(race)){
                    break;
                }else
                    continue;
            }
        }
    }
    table_name_output_all_race(race);
    std::cout << "The race has begun\nNow we will find out the winners\n";
    race->bubble_sort_transport();
    table_name_time_output_all_race(race);
}
// win ground = CamelIsFast, Centaur, Camel, AllTerrainBoots
// win air = Broomstick, MagicCarpet, Eagle
// win air and ground = CamelIsFast, Broomstick, Centaur, MagicCarpet/Camel, Eagle, AllTerrainBoots

int main() {
    int choice_race = greeting_out_and_choice();
    int distance = distance_sampling();
    switch (choice_race){
        case 1: game_race_air(distance); break;
        case 2: game_race_ground(distance); break;
        case 3: game_race_air_and_ground(distance); break;
    }
    std::cout <<std::setw(25) << "!Game over!";
    return 0;
}