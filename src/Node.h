#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <unordered_map>

class Node{

    /*
    * *.sgnd files are formatted as follows
    * Groups are seperated by ascii group seperator characters
    * Usages of ':' represent usages of the ascii record seperator
    * Usages of ',' represent usages of the ascii unit seperator
    * 
    * Group 0 (identification)    <node_id>:<node_name>
    * Group 1 (connections)       <reference_count>:<connection_ids>
    * Group 2 (data)              <key_1>,<value_1>:<key_2>,<value_2>:...:<key_e>,<value_e>
    */

    private:
        // ID the node will be refered to by
        int id;

        // Text name used for searching + readability
        std::string name;

        // number of nodes that point to this node
        int reference_count;

        // Nodes this node points to
        std::vector<int> connection_ids;

        // string to be appended after node id to get file name
        std::string FILE_EXT = "_data.sgnd";

        // path to this nodes file
        std::string filepath;

        // non-control data stored in the node
        std::unordered_map<std::string, std::string>* node_contents = NULL;

        bool data_loaded = false;

        bool data_changed = false;

        enum GroupId{ identification = 0, connections = 1, data = 2};
        // Read requested data group based on enum
        std::string read_data_group(Node::GroupId group_id);
        // Returns only the requested data group
        std::string read_data_group_id(int& group_id);
        // Returns an array split into the three data groups
        std::string* read_data_groups();

        // How many bytes to increment the buffer by when reading data
        int SIZE_INC = 100;
    public:

        // Load node from file
        Node(std::string& folder, int& id);
        // Create Node with id and name
        Node(std::string& folder, int& id, std::string& name);

        // ID of this node
        int& get_id();

        // Name of this node
        std::string& get_name();

        // Get ids of the connected nodes
        std::vector<int>& get_connection_ids();

        // Increments the reference counter
        void add_reference();
        // Get count of nodes pointing to this node
        int& get_reference_count();
        // Decrements the reference counter
        void remove_reference();

        // Adds connection to target node
        void add_connection(int& targetId);
        // Removes connection from this node to the target
        void remove_connection(int& targetId);

        // Returns if the data is currently loaded
        bool& is_loaded();
        // Loads data from file into memory
        // If data is already loaded it will NOT reload data
        void load_data();
        // Writes data to disk
        void write_data();
        // Dumps data out of memory, calls write_data first if changes
        void dump_data();
        
        // Returns the value of the key, null if key is not in map
        // if data is not loaded this method will cause data to be loaded
        std::string& get_value(std::string key);
        // Sets the value of a key
        // if data is not loaded this method will cause data to be loaded
        void set_value(std::string key, std::string value);
        // Erases the key and the value associated with that key
        // if data is not loaded this method will cause data to be loaded
        void erase_value(std::string key);

        // Deletes the file this node references, the object will not be lost
        // Returns false if the node failed to delete
        bool delete_node();

        // Delete unordered map
        ~Node();
};
#endif