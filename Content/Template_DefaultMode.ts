import * as UE from "ue";
import { blueprint } from "puerts";

const bpClass = UE.Class.Load("/*BlueprintPathName*/_C");
const jsClass = blueprint.tojs<typeof UE/*BlueprintPathName_Dot*/_C>(bpClass);

interface /*BlueprintName*/ extends UE/*BlueprintPathName_Dot*/_C { }

class /*BlueprintName*/ {
/*PlaceholderOverrides*/
}

blueprint.mixin(jsClass, /*BlueprintName*/);