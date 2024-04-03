// Listing 4.23 Gathering results from futures using std::experimental::when_all
std::experimental::future<FinalResult> process_data(
    std::vector<MyData>& vec)
{
    size_t const chunk_size=whatever;
    std::vector<std::experimental::future<ChunkResult>> results;
    for(auto begin=vec.begin(),end=vec.end();beg!=end;){
        size_t const remaining_size=end-begin;
        size_t const this_chunk_size=std::min(remaining_size,chunk_size);
        results.push_back(
            spawn_async(
            process_chunk,begin,begin+this_chunk_size));
        begin+=this_chunk_size;
    }
    return std::experimental::when_all(
        // 1.you use when_all to wait for all the futures to become ready, 
        // and then schedule the function using .then rather than async.
        results.begin(),results.end()).then(
        [](std::future<std::vector<
             std::experimental::future<ChunkResult>>> ready_results)
        {
            std::vector<std::experimental::future<ChunkResult>>
                all_results=ready_results .get();
            std::vector<ChunkResult> v;
            v.reserve(all_results.size());
            for(auto& f: all_results)
            {
                // 2.the calls to get on the futures do not block, 
                // as all the values are ready by the time execution gets there.
                v.push_back(f.get());
            }
            return gather_results(v);
        });
}
