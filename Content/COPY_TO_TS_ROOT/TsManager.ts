import * as UE from "ue";
import { blueprint } from "puerts";

const bpClass = UE.Class.Load("/TsMixinTool/BP_TsManagerProxy.BP_TsManagerProxy_C");
const mixinClass = blueprint.tojs<typeof UE.TsMixinTool.BP_TsManagerProxy.BP_TsManagerProxy_C>(bpClass);

interface TsManagerProxy extends UE.TsMixinTool.BP_TsManagerProxy.BP_TsManagerProxy_C { }

const TsMap: Map<string, typeof TsClass> = new Map();

class TsManagerProxy {
    Initialize(): void {
        console.log("[TsManager] TsManagerProxy Initialize");
    }

    async Register(uObj: UE.Object) {
        const bpName = uObj.GetClass().GetName();

        if (TsMap.has(bpName)) {
            const tsClass = TsMap.get(bpName);
            if (!tsClass) {
                console.error(`[TsManager] Class ${bpName} is registered but not found in TsMap.`);
                return;
            }
            const tsInstance = new tsClass();
            tsInstance.Initialize(uObj);
        } else {
            const tsClass = await this.LoadTsClass(uObj);
            if (!tsClass) {
                return;
            }
            TsMap.set(bpName, tsClass);

            const tsInstance = new tsClass();
            tsInstance.Initialize(uObj);
        }
    }

    async LoadTsClass(uObj: UE.Object) {
        const bpName = uObj.GetClass().GetName().slice(0, -2);
        try {
            const bpPathName = UE.TsManagerSubsystem.GetBPAssetPath(uObj).slice(0, -(bpName.length + 1));
            const modulePath = `./TsScripts_Manager/${bpPathName}`;
            const module = await import(modulePath);
            const tsClassCtor = module[bpName] as typeof TsClass;
            if (!tsClassCtor) {
                console.error(`[TsManager] Class ${bpName} not found in module: ${modulePath}`);
                return null;
            }
            return tsClassCtor;
        } catch (err) {
            console.error(`[TsManager] Failed to load TS class: ${bpName}`, err);
            return null;
        }
    }
}

blueprint.mixin(mixinClass, TsManagerProxy);