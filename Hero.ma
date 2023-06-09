[Top]
components : Hero 
out : heroOut creepOut resultOut 
in : creepIn heroIn
Link : creepIn creepIn@Hero
Link : heroIn heroIn@Hero
Link : heroOut@Hero heroOut
Link : creepOut@Hero creepOut
Link : resultOut@Hero resultOut

[Hero]
components : HDecision@HDecision HAttack@HAttack
out : creepOut heroOut resultOut 
in : heroIn creepIn 
Link : attackOut@HDecision in@HAttack
Link : creepOut@HAttack creepOut
Link : heroOut@HAttack heroOut
Link : resultOut@HAttack resultOut
Link : heroIn heroIn@HDecision
Link : creepIn creepIn@HDecision

[HDecision]

[HAttack]



