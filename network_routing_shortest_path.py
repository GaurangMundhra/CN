import sys

V = 5  # Number of vertices

# Function to find the vertex with the minimum distance value
def min_distance(dist, spt_set):
    min_val = sys.maxsize
    min_index = -1
    for v in range(V):
        if not spt_set[v] and dist[v] < min_val:
            min_val = dist[v]
            min_index = v
    return min_index

# Function to print the path from source to destination
def print_path(parent, j):
    if parent[j] == -1:
        print(j, end='')
        return
    print_path(parent, parent[j])
    print(" ->", j, end='')

# Dijkstra's algorithm
def dijkstra(graph, src, dest):
    dist = [sys.maxsize] * V
    parent = [-1] * V
    spt_set = [False] * V

    dist[src] = 0

    for _ in range(V - 1):
        u = min_distance(dist, spt_set)
        spt_set[u] = True

        for v in range(V):
            if (graph[u][v] > 0 and not spt_set[v] and
                dist[u] + graph[u][v] < dist[v]):
                dist[v] = dist[u] + graph[u][v]
                parent[v] = u

    print(f"\nShortest path from node {src} to {dest} is {dist[dest]}")
    print("Path:", end=' ')
    print_path(parent, dest)
    print()

# Main execution
if __name__ == "__main__":
    graph = [
        [0, 10, 20, 0, 0],
        [10, 0, 5, 16, 0],
        [20, 5, 0, 2, 30],
        [0, 16, 2, 0, 8],
        [0, 0, 30, 8, 0]
    ]

    try:
        src = int(input(f"Enter source node (0-{V - 1}): "))
        dest = int(input(f"Enter destination node (0-{V - 1}): "))

        if 0 <= src < V and 0 <= dest < V:
            dijkstra(graph, src, dest)
        else:
            print("Invalid input. Please enter nodes between 0 and", V - 1)
    except ValueError:
        print("Please enter valid integers.")


# Algorithm Overview:

# Start at the source node and set its distance to 0.

# For all other nodes, set the initial distance to infinity (sys.maxsize).

# Use a greedy approach to choose the node with the smallest known distance, and explore its neighbors.

# Update the distance for each neighbor if a shorter path is found.

# Repeat until all nodes have been visited.

# Time Complexity: 
# 𝑂(𝑉2), O(V2) for the basic implementation (where V is the number of vertices), due to the repeated scan of all vertices in the min_distance() function.
# Space Complexity: 𝑂(𝑉), O(V) for storing the distance, parent, and processed node arrays.

# min_distance: Finds the vertex with the smallest unprocessed distance.

# print_path: Recursively prints the shortest path using the parent array.

# dijkstra: Runs Dijkstra's algorithm to find the shortest path from src to dest and prints it.

# Main Execution: Accepts user input and calls the dijkstra function to compute and display the shortest path.