import "./TsManager"
import { TsClass as _TsClass } from "./TsClass";

(globalThis as any).TsClass = _TsClass;

console.log("========== TypeScript MainGame Init ==========");
