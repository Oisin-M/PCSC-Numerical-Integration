file(REMOVE_RECURSE
  "Tests.pdb"
  "Tests"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Tests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
