#ifndef TRAFFIC_ENGINE_H
#define TRAFFIC_ENGINE_H

#include <vector>
#include <map>
#include <string>
#include <chrono>

// Structure to represent a traffic intersection
struct Intersection {
    int id;
    double latitude;
    double longitude;
    std::vector<int> connected_intersections;
    std::map<std::string, int> vehicle_count; // direction -> count
    std::map<std::string, int> signal_state; // direction -> signal state (0=red, 1=green)
    int congestion_level; // 0-100
};

// Structure to represent a vehicle
struct Vehicle {
    int id;
    double latitude;
    double longitude;
    double speed;
    std::string direction;
    std::string vehicle_type; // car, bus, truck, etc.
    long long timestamp;
};

// Structure to represent traffic flow data
struct TrafficFlow {
    int intersection_id;
    int vehicles_per_minute;
    double average_speed;
    int congestion_level;
    long long timestamp;
};

class TrafficEngine {
public:
    TrafficEngine();
    ~TrafficEngine();
    
    // Initialize the traffic management system
    void initialize(const std::string& config_file);
    
    // Add/update vehicle data
    void add_vehicle(const Vehicle& vehicle);
    void update_vehicle(const Vehicle& vehicle);
    void remove_vehicle(int vehicle_id);
    
    // Get intersection data
    Intersection* get_intersection(int intersection_id);
    std::vector<Intersection*> get_all_intersections();
    
    // Process traffic and optimize signals
    void process_traffic();
    void optimize_traffic_signals();
    
    // Get real-time traffic data
    TrafficFlow get_traffic_flow(int intersection_id);
    std::vector<Vehicle> get_vehicles_at_intersection(int intersection_id);
    
    // Congestion analysis
    int calculate_congestion_level(int intersection_id);
    bool is_congested(int intersection_id);
    
private:
    std::vector<Intersection> intersections;
    std::map<int, Vehicle> vehicles;
    std::chrono::system_clock::time_point last_update;
    
    // Helper functions
    void update_congestion_levels();
    void apply_optimization_algorithm();
};

#endif // TRAFFIC_ENGINE_H