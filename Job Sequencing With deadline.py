def job_sequencing_optimized(jobs):
    jobs.sort(reverse=True, key=lambda x: x[0])
    max_deadline = max(jobs, key=lambda x: x[1])[1]
    parent = list(range(max_deadline + 1))
    
    def find(slot):
        if parent[slot] == slot:
            return slot
        parent[slot] = find(parent[slot])
        return parent[slot]
    
    total_profit = 0
    count = 0
    
    for profit, deadline in jobs:
        available_slot = find(deadline)
        if available_slot > 0:
            total_profit += profit
            count += 1
            parent[available_slot] = find(available_slot - 1)
    
    return count, total_profit